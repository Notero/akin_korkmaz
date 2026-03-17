import {Ratelimit} from "@upstash/ratelimit";
import {Redis} from "@upstash/redis";

import dotenv from 'dotenv';


dotenv.config({ 
  path: ['.env.local', '.env'] 
});

//limiter that allows 5 req per 60 secs
const rateLimit = new Ratelimit({
    redis: Redis.fromEnv(),
    limiter: Ratelimit.slidingWindow(20, "60 s")
});

export default rateLimit;