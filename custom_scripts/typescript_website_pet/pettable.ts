// ── DOM Setup ─────────────────────────────────────────────────────────────────

const pettable_host = document.createElement('div');
pettable_host.id = 'pettable-host';
pettable_host.style.cssText = 'position:fixed;top:0;left:0;width:100%;height:100%;pointer-events:none;z-index:9999;';
document.body.appendChild(pettable_host);

const shadowEntity = pettable_host.attachShadow({ mode: 'open' });

const pettable_canvas = document.createElement('canvas');
pettable_canvas.id = 'pettable-canvas';
pettable_canvas.width  = window.innerWidth;
pettable_canvas.height = window.innerHeight;
pettable_canvas.style.cssText = 'position:fixed;top:0;left:0;pointer-events:auto;cursor:pointer;';
shadowEntity.appendChild(pettable_canvas);

// ── Types ─────────────────────────────────────────────────────────────────────

type BehaviorState  = 'idle' | 'chase' | 'wander' | 'sleeping' | 'runaway';
type AnimationState = 'sittingDown' | 'lookingAround' | 'layingDown' | 'walking' | 'running' | 'runningFast';

const STAGGER_FRAMES = 15;

// ── Pettable ──────────────────────────────────────────────────────────────────

class Pettable {
    private SpriteSheet: HTMLImageElement;
    private ctx: CanvasRenderingContext2D | null;

    // Sprite config
    private readonly COLUMNS = 32;
    private readonly ROWS    = 17;
    private readonly SCALE   = 2;
    private spriteWidth  = 0;
    private spriteHeight = 0;

    // OPT: cached scaled dimensions, computed once after sprite loads
    private scaledW = 0;
    private scaledH = 0;

    // Position
    private currPosX = 0;
    private currPosY = 0;

    // Mouse (live) — throttled
    private mouseX = -9999;
    private mouseY = -9999;
    private lastMouseUpdate = 0;
    private readonly MOUSE_THROTTLE_MS = 32; // ~30fps is plenty for cat chasing

    // Targets per state
    private chaseTargetX  = 0;
    private chaseTargetY  = 0;
    private wanderTargetX = 0;
    private wanderTargetY = 0;
    private runawayTargetX = 0;
    private runawayTargetY = 0;

    // ── Behavior state ────────────────────────────────────────────────────────
    private behaviorState: BehaviorState = 'idle';

    // Idle cycling
    private idleSubAnim: 'sittingDown' | 'lookingAround' = 'sittingDown';
    private idleSubTimer = 0;
    private readonly IDLE_LOOK_INTERVAL = 8000;
    private readonly IDLE_LOOK_DURATION = 4000;

    // Auto-sleep (resets on every click)
    private lastClickTime = 0;
    private readonly AUTO_SLEEP_AFTER = 30_000;

    // Auto-wake
    private sleepStartTime = 0;
    private readonly AUTO_WAKE_AFTER = 120_000;

    // Wander waypoint pausing
    private wanderPausing  = false;
    private wanderPauseEnd = 0;
    private readonly WANDER_PAUSE_MIN = 2000;
    private readonly WANDER_PAUSE_MAX = 8000;

    // ── Animation ─────────────────────────────────────────────────────────────
    private currentAnimation: AnimationState = 'sittingDown';
    private currentFrame = 0;
    private frameTick    = 0;
    private direction    = 0;

    // OPT: dirty flag — skip redraw if nothing changed (key for idle/sleeping)
    private dirty = true;

    // OPT: track last rendered position/frame to detect actual changes
    private lastDrawnX     = -1;
    private lastDrawnY     = -1;
    private lastDrawnFrame = -1;
    private lastDrawnAnim: AnimationState | '' = '';
    private lastDrawnDir   = -1;

    private readonly animDefs: Record<AnimationState, [number, number][]> = {
        sittingDown:   [ [1,0],[1,1],[1,2],[1,3],[2,0],[2,1] ],
        lookingAround: [ [1,4],[1,5],[1,6],[1,7],[2,4],[1,7],[1,6],[1,5] ],
        layingDown:    [ [1,8],[1,9],[1,10],[1,11],[2,8],[2,9],[2,10],[2,11] ],
        walking:       [ [1,12],[1,13],[1,14],[1,15] ],
        running:       [ [1,16],[1,17],[1,18],[1,19],[2,16] ],
        runningFast:   [ [1,20],[1,21],[1,22],[1,23],[2,20],[2,21],[2,22],[2,23] ],
    };

    // ── Constructor ───────────────────────────────────────────────────────────

    constructor() {
        const now = Date.now();
        this.lastClickTime = now;
        this.idleSubTimer  = now;

        this.SpriteSheet     = new Image();
        this.SpriteSheet.src = './catSprites/pink_0.png';
        this.SpriteSheet.onload = () => {
            this.spriteWidth  = this.SpriteSheet.width  / this.COLUMNS;
            this.spriteHeight = this.SpriteSheet.height / this.ROWS;

            // OPT: cache scaled dimensions once
            this.scaledW = this.spriteWidth  * this.SCALE;
            this.scaledH = this.spriteHeight * this.SCALE;

            this.currPosX     = window.innerWidth  / 4 - this.scaledW / 2;
            this.currPosY     = window.innerHeight / 4 - this.scaledH / 2;
            this.chaseTargetX = this.currPosX;
            this.chaseTargetY = this.currPosY;
            this.dirty = true;
            this.animate();
        };

        this.ctx = pettable_canvas.getContext('2d');
        if (this.ctx) this.ctx.imageSmoothingEnabled = false;

        // OPT: throttled mousemove — cat doesn't need full 60fps mouse data
        window.addEventListener('mousemove', (e) => {
            const now = Date.now();
            if (now - this.lastMouseUpdate < this.MOUSE_THROTTLE_MS) return;
            this.mouseX = e.clientX;
            this.mouseY = e.clientY;
            this.lastMouseUpdate = now;
        });

        pettable_canvas.addEventListener('click', (e) => {
            this.lastClickTime = Date.now();
            if (this.isPointOnCat(e.clientX, e.clientY)) {
                this.onCatClick();
            }
        });

        // OPT: handle canvas resize
        window.addEventListener('resize', () => {
            pettable_canvas.width  = window.innerWidth;
            pettable_canvas.height = window.innerHeight;
            if (this.ctx) this.ctx.imageSmoothingEnabled = false;
            this.dirty = true;
        });
    }

    // ── Hit test ─────────────────────────────────────────────────────────────

    private isPointOnCat(x: number, y: number): boolean {
        return x >= this.currPosX && x <= this.currPosX + this.scaledW
            && y >= this.currPosY && y <= this.currPosY + this.scaledH;
    }

    // ── Click handlers ────────────────────────────────────────────────────────
    currClick: number = 0;

    private onCatClick() {
        this.currClick++;
        console.log(`Cat clicked! Total clicks: ${this.currClick}`);
        switch (this.currClick % 5) {
            case 0: this.enterIdle();    break;
            case 1: this.enterChase();   break;
            case 2: this.enterWander();  break;
            case 3: this.enterSleeping();break;
            case 4: this.enterRunaway(); break;
        }
    }

    // ── State entry ───────────────────────────────────────────────────────────

    private enterIdle() {
        this.behaviorState = 'idle';
        this.idleSubAnim   = 'sittingDown';
        this.idleSubTimer  = Date.now();
        this.setAnim('sittingDown');
    }

    private enterChase() {
        this.behaviorState = 'chase';
        this.pickChaseTarget();
        this.setAnim('walking');
    }

    private pickChaseTarget() {
        const margin = 80;
        this.chaseTargetX = Math.max(margin, Math.min(pettable_canvas.width  - margin, this.mouseX - this.scaledW / 2));
        this.chaseTargetY = Math.max(margin, Math.min(pettable_canvas.height - margin, this.mouseY - this.scaledH / 2));
    }

    private enterWander() {
        this.behaviorState = 'wander';
        this.wanderPausing = false;
        this.pickWanderTarget();
    }

    private enterSleeping() {
        this.behaviorState  = 'sleeping';
        this.sleepStartTime = Date.now();
        this.setAnim('layingDown');
    }

    private enterRunaway() {
        this.behaviorState = 'runaway';
        this.pickRunawayTarget();
        this.setAnim('runningFast');
    }

    // ── Ticks ─────────────────────────────────────────────────────────────────

    // OPT: all ticks receive a pre-computed `now` — no repeated Date.now() calls per frame
    private tickIdle(now: number) {
        if (now - this.lastClickTime > this.AUTO_SLEEP_AFTER) {
            this.enterSleeping();
            return;
        }

        const elapsed = now - this.idleSubTimer;
        if (this.idleSubAnim === 'sittingDown' && elapsed > this.IDLE_LOOK_INTERVAL) {
            this.idleSubAnim  = 'lookingAround';
            this.idleSubTimer = now;
            this.setAnim('lookingAround');
        } else if (this.idleSubAnim === 'lookingAround' && elapsed > this.IDLE_LOOK_DURATION) {
            this.idleSubAnim  = 'sittingDown';
            this.idleSubTimer = now;
            this.setAnim('sittingDown');
        }
    }

    private tickChase(now: number) {
        this.pickChaseTarget();

        const dx   = this.chaseTargetX - this.currPosX;
        const dy   = this.chaseTargetY - this.currPosY;
        const dist = Math.sqrt(dx * dx + dy * dy);

        this.updateDirectionToward(
            this.chaseTargetX + this.scaledW / 2,
            this.chaseTargetY + this.scaledH / 2
        );

        if (dist > 8) {
            if (dist < 200) {
                this.setAnim('walking');
                this.moveToward(this.chaseTargetX, this.chaseTargetY, 1);
            } else if (dist < 450) {
                this.setAnim('running');
                this.moveToward(this.chaseTargetX, this.chaseTargetY, 2);
            } else {
                this.setAnim('runningFast');
                this.moveToward(this.chaseTargetX, this.chaseTargetY, 3);
            }
            this.dirty = true;
        } else if (now - this.lastClickTime > this.AUTO_SLEEP_AFTER) {
            this.enterSleeping();
        }
    }

    private tickWander(now: number) {
        if (this.wanderPausing) {
            this.setAnim('sittingDown');
            if (now >= this.wanderPauseEnd) {
                this.wanderPausing = false;
                this.pickWanderTarget();
            }
            return;
        }

        const dx   = this.wanderTargetX - this.currPosX;
        const dy   = this.wanderTargetY - this.currPosY;
        const dist = Math.sqrt(dx * dx + dy * dy);

        this.updateDirectionToward(
            this.wanderTargetX + this.scaledW / 2,
            this.wanderTargetY + this.scaledH / 2
        );

        if (dist > 8) {
            this.setAnim('walking');
            this.moveToward(this.wanderTargetX, this.wanderTargetY, 1);
            this.dirty = true;
        } else {
            this.wanderPausing  = true;
            this.wanderPauseEnd = now + this.WANDER_PAUSE_MIN
                + Math.random() * (this.WANDER_PAUSE_MAX - this.WANDER_PAUSE_MIN);
        }

        if (now - this.lastClickTime > this.AUTO_SLEEP_AFTER) {
            this.enterSleeping();
        }
    }

    private tickSleeping(now: number) {
        if (now - this.sleepStartTime > this.AUTO_WAKE_AFTER) {
            this.lastClickTime = now;
            this.enterIdle();
        }
    }

    private tickRunaway() {
        const dx   = this.runawayTargetX - this.currPosX;
        const dy   = this.runawayTargetY - this.currPosY;
        const dist = Math.sqrt(dx * dx + dy * dy);

        this.updateDirectionToward(
            this.runawayTargetX + this.scaledW / 2,
            this.runawayTargetY + this.scaledH / 2
        );

        if (dist > 12) {
            this.setAnim('runningFast');
            this.moveToward(this.runawayTargetX, this.runawayTargetY, 4);
            this.dirty = true;
        } else {
            this.enterIdle();
        }
    }

    // ── Helpers ───────────────────────────────────────────────────────────────

    private moveToward(tx: number, ty: number, speed: number) {
        const dx   = tx - this.currPosX;
        const dy   = ty - this.currPosY;
        const dist = Math.sqrt(dx * dx + dy * dy);
        if (dist === 0) return;
        this.currPosX += (dx / dist) * speed;
        this.currPosY += (dy / dist) * speed;
    }

    private updateDirectionToward(worldX: number, worldY: number) {
        const catCX = this.currPosX + this.scaledW / 2;
        const catCY = this.currPosY + this.scaledH / 2;
        const dx = worldX - catCX;
        const dy = worldY - catCY;

        const deg = ((Math.atan2(dy, dx) * 180 / Math.PI) + 360) % 360;
        if      (deg >= 337.5 || deg <  22.5) this.direction = 6; // right
        else if (deg <  67.5)                 this.direction = 7; // down-right
        else if (deg <  112.5)                this.direction = 0; // down
        else if (deg <  157.5)                this.direction = 1; // down-left
        else if (deg <  202.5)                this.direction = 2; // left
        else if (deg <  247.5)                this.direction = 3; // up-left
        else if (deg <  292.5)                this.direction = 4; // up
        else                                  this.direction = 5; // up-right
    }

    private pickWanderTarget() {
        const margin = 80;
        this.wanderTargetX = margin + Math.random() * (pettable_canvas.width  - margin * 2);
        this.wanderTargetY = margin + Math.random() * (pettable_canvas.height - margin * 2);
    }

    private pickRunawayTarget() {
        const angle  = Math.atan2(this.currPosY - this.mouseY, this.currPosX - this.mouseX);
        const spread = (Math.random() - 0.5) * (Math.PI / 3);
        const dist   = 350 + Math.random() * 200;

        this.runawayTargetX = Math.max(0, Math.min(
            pettable_canvas.width  - this.scaledW,
            this.currPosX + Math.cos(angle + spread) * dist
        ));
        this.runawayTargetY = Math.max(0, Math.min(
            pettable_canvas.height - this.scaledH,
            this.currPosY + Math.sin(angle + spread) * dist
        ));
    }

    private setAnim(anim: AnimationState) {
        if (this.currentAnimation !== anim) {
            this.currentAnimation = anim;
            this.currentFrame     = 0;
            this.dirty = true;
        }
    }

    // ── Main loop ─────────────────────────────────────────────────────────────

    animate = () => {
        // OPT: single Date.now() call for the entire frame
        const now = Date.now();

        switch (this.behaviorState) {
            case 'idle':     this.tickIdle(now);     break;
            case 'chase':    this.tickChase(now);    break;
            case 'wander':   this.tickWander(now);   break;
            case 'sleeping': this.tickSleeping(now); break;
            case 'runaway':  this.tickRunaway();     break;
        }

        // Frame advancement
        const frames = this.animDefs[this.currentAnimation];
        if (this.currentFrame >= frames.length) this.currentFrame = 0;

        if (this.frameTick % STAGGER_FRAMES === 0) {
            const oneShot =
                this.currentAnimation === 'sittingDown' ||
                this.currentAnimation === 'layingDown';

            const nextFrame = oneShot
                ? Math.min(this.currentFrame + 1, frames.length - 1)
                : (this.currentFrame + 1) % frames.length;

            if (nextFrame !== this.currentFrame) {
                this.currentFrame = nextFrame;
                this.dirty = true;
            }
        }

        // OPT: skip draw entirely if position, frame, anim, and direction haven't changed
        const needsDraw =
            this.dirty ||
            this.currPosX     !== this.lastDrawnX     ||
            this.currPosY     !== this.lastDrawnY     ||
            this.currentFrame !== this.lastDrawnFrame ||
            this.currentAnimation !== this.lastDrawnAnim ||
            this.direction    !== this.lastDrawnDir;

        if (needsDraw && this.ctx) {
            const [row, col] = frames[this.currentFrame];
            const isMoving =
                this.currentAnimation === 'walking'    ||
                this.currentAnimation === 'running'    ||
                this.currentAnimation === 'runningFast';

            const srcRow = isMoving ? row + this.direction * 2 : row;
            const srcX   = col * this.spriteWidth;
            const srcY   = srcRow * this.spriteHeight;

            // OPT: clear only the previous cat bounding box, not the full canvas
            // We pad by 1px to avoid sub-pixel ghosting at boundaries
            this.ctx.clearRect(
                this.lastDrawnX - 1,
                this.lastDrawnY - 1,
                this.scaledW + 2,
                this.scaledH + 2
            );

            // OPT: use canvas clip instead of setting clipPath on the DOM element every frame
            this.ctx.save();
            this.ctx.beginPath();
            this.ctx.rect(this.currPosX, this.currPosY, this.scaledW, this.scaledH);
            this.ctx.clip();

            this.ctx.drawImage(
                this.SpriteSheet,
                srcX, srcY, this.spriteWidth, this.spriteHeight,
                this.currPosX, this.currPosY, this.scaledW, this.scaledH
            );

            this.ctx.restore();

            // Update last drawn state
            this.lastDrawnX     = this.currPosX;
            this.lastDrawnY     = this.currPosY;
            this.lastDrawnFrame = this.currentFrame;
            this.lastDrawnAnim  = this.currentAnimation;
            this.lastDrawnDir   = this.direction;
            this.dirty = false;
        }

        this.frameTick++;
        requestAnimationFrame(this.animate);
    };
}

// Boot
const myPet = new Pettable();