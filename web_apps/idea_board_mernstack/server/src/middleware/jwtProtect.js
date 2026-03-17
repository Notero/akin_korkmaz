import jwt from 'jsonwebtoken';
import User from '../models/User.js';
import { asyncHandler } from '../utils/asyncHandler.js';

export const protect = asyncHandler(async (req, res, next) => {
    let token;

    // 1. Look for the token in the cookies instead of the header
    token = req.cookies.token;

    if (token) {
        try {
            // 2. Verify the token
            const decoded = jwt.verify(token, process.env.JWT_SECRET);

            // 3. Admin logic (unchanged)
            if (decoded.role && decoded.role === 'admin') {
                req.user = { role: 'admin' };
                return next();
            }

            // 4. Find the user and attach to req.user
            req.user = await User.findById(decoded.userId).select('-password');

            if (!req.user) {
                res.status(401);
                throw new Error('User no longer exists');
            }

            next();
        } catch (error) {
            console.error(error);
            res.status(401);
            throw new Error('Not authorized, token failed');
        }
    } else {
        // 5. If no cookie is found
        res.status(401);
        throw new Error('Not authorized, no token provided');
    }
});