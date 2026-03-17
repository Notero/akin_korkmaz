import jwt from "jsonwebtoken"; // For token generation
import dotenv from 'dotenv';
import {asyncHandler} from '../utils/asyncHandler.js'; // Assuming you saved it 


dotenv.config({ 
  path: ['.env.local', '.env'] 
});

export const generateAdminToken = asyncHandler(async (req, res) => {
    var payload = {
        role: 'admin'
    };

    const token = jwt.sign(payload, process.env.JWT_SECRET, { expiresIn: '23h' });
    res.status(200).json({ token : token });
});