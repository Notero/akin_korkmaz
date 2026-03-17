import express from 'express';
import cors from 'cors';
import dotenv from 'dotenv';

import adminTokenRouter from './routes/adminTokenRoute.js';
import ideaRouter from './routes/IdeaRouter.js';
import boardRouter from './routes/boardRouter.js';
import userRouter from './routes/userRouter.js';
import { connectDB } from './config/db.js';
import  rateLimiter  from './middleware/rateLimiter.js';
import cookieParser from 'cookie-parser'; // Import cookie-parser to handle cookies

//Extension IDEAS
//Real-Time "Whiteboard"
//Idea Board with drag-and-drop
//Birthday Reminder for added People
//Developer Portfolio with a "Live" CMS
//Personal Finance & Subscription Tracker
//Collaborative Task & Project Board

dotenv.config({ 
  path: ['.env.local', '.env'] 
});

const app = express();
const PORT = process.env.PORT || 8001;

const corsOptions = {
    origin: 'http://localhost:5173',
    methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'],
    credentials: true,
    allowedHeaders: ['Content-Type', 'Authorization']
};

app.use(cors(corsOptions));
app.use(cookieParser()); // Middleware to parse cookies from incoming requests

//Json middleware to parse incoming JSON requests
app.use(express.json());
app.use(rateLimiter); // Apply rate limiter middleware to all routes

app.use("/admin-token", adminTokenRouter);
app.use("/api/board", boardRouter);
app.use("/api/idea", ideaRouter);
app.use("/api/user", userRouter);

// Global Error Handler
app.use((err, req, res, next) => {
    const statusCode = res.statusCode === 200 ? 500 : res.statusCode;
    res.status(statusCode).json({
        message: err.message
    });
});


connectDB().then(() => {
    app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
}
).catch((error) => {
    console.error('Failed to connect to MongoDB:', error);
    process.exit(1); // Exit with failure code
});

