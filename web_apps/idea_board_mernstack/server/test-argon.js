import argon2 from "argon2";
const start = Date.now();
const hash = await argon2.hash("password");
console.log("Hash time:", Date.now() - start);
const start2 = Date.now();
await argon2.verify(hash, "password");
console.log("Verify time:", Date.now() - start2);
