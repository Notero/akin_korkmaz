import { connectDB } from './src/config/db.js';
import Idea from './src/models/Idea.js';
import dotenv from 'dotenv';
dotenv.config({ path: ['.env.local', '.env'] });

async function checkIdeas() {
  await connectDB();
  const ideas = await Idea.find({}).limit(5);
  console.log("Ideas:", ideas);
  process.exit(0);
}
checkIdeas();
