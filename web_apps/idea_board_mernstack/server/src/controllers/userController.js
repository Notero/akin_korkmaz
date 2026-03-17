import User from "../models/User.js";
import {asyncHandler} from '../utils/asyncHandler.js'; // Assuming you saved it 
import argon2 from "argon2"; // For password hashing
import jwt from "jsonwebtoken"; // For token generation (if needed)
import dotenv from 'dotenv';

dotenv.config({ 
  path: ['.env.local', '.env'] 
});

// 1. Register User Controller
export const registerUser = asyncHandler(async (req, res) => {
    
    const { email, username, password } = req.body;

    if (!email || !username || !password) {
        res.status(400);
        throw new Error("Please provide email, username, and password!");
    }

    // Check if user already exists
    const existingUser = await User.findOne({ email }).lean();
    if (existingUser) {
        res.status(400);
        throw new Error("User already exists with this email!");
    }

    // Hash the password before saving
    const hashedPassword = await argon2.hash(password);

    //Create new user
    const newUser = await User.create({ email, username, password: hashedPassword });

    if (!newUser) {
        res.status(500);
        throw new Error("Failed to create user!");
    }else{
        res.status(201).json({ message: "User registered successfully", user: { email: newUser.email, username: newUser.username } });
    }
});


// 2. Login User Controller
export const loginUser = asyncHandler(async (req, res) => {
    const { email, password } = req.body;

    //verify that email and password are provided
    if (!email || !password) {
        res.status(400);
        throw new Error("Please provide email and password!");
    }
    
    // Find user by email
    const user = await User.findOne({ email }).lean();

    if (!user) {
        res.status(400);
        throw new Error("Invalid email or password!");
    }

    // Verify password
    const isPasswordValid = await argon2.verify(user.password, password);
    
    if (!isPasswordValid) {
        res.status(400);
        throw new Error("Invalid email or password!");
    }

    // If login is successful, you can generate a token here (e.g., JWT) and send it back to the client
    const token = jwt.sign({ userId: user._id }, process.env.JWT_SECRET, { expiresIn: '24h' });

    res.cookie('token', token, {
        httpOnly: true,
        secure: false, // Set to true in production (requires HTTPS)
        sameSite: 'lax', // Adjust as needed (e.g., 'lax' or 'none' if you have cross-origin requests)
        maxAge: 24 * 60 * 60 * 1000 // 1 day
    });

    res.status(200).json({ message: "Login successful", user: { email: user.email, username: user.username , userId: user._id} });
});

// 3. Get User Profile Controller
export const getUserProfile = asyncHandler(async (req, res) => {
    const user = await User.findById(req.user._id).select('-password'); // Exclude password from the response
    if (!user) {
        res.status(404);
        throw new Error("User not found!");
    }
    res.status(200).json(user);
});
// 4. Update User Profile Controller
export const updateUserProfile = asyncHandler(async (req, res) => {
    const { email, username, password } = req.body;
    
    const user = await User.findById(req.user._id);

    if (!user) {
        res.status(404);
        throw new Error("User not found!");
    }

    // Update fields if provided
    if(email !== undefined) user.email = email;
    if(username !== undefined) user.username = username;
    if(password !== undefined) user.password = await argon2.hash(password); // Hash new password

    const updatedUser = await user.save();
    
    if (!updatedUser) {
        res.status(500);
        throw new Error("Failed to update user profile!");
    }

    res.status(200).json({ message: "Profile updated successfully", user: { email: updatedUser.email, username: updatedUser.username } });
    
});

// 5. Delete User Account Controller

export const deleteUserAccount = asyncHandler(async (req, res) => {
    const user = await User.findById(req.user._id);

    if (!user) {
        res.status(404);
        throw new Error("User not found!");
    }

    const result = await User.deleteOne({ _id: req.user._id });
    if (result.deletedCount === 0) {
        res.status(500);
        throw new Error("Failed to delete user account!");
    }
    
    res.status(200).json({ message: "User account deleted successfully" });
});
