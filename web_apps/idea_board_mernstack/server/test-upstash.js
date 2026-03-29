import rateLimit from "./src/config/upstash.js";
const start = Date.now();
try {
  await rateLimit.limit("127.0.0.1");
  console.log("Upstash time:", Date.now() - start);
} catch(e) {
  console.log("Error:", e.message);
}
