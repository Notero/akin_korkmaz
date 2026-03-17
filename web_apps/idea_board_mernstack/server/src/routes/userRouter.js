import express from 'express';
import { registerUser, loginUser, updateUserProfile, deleteUserAccount, getUserProfile } from '../controllers/userController.js';
import { protect } from '../middleware/jwtProtect.js';

const router = express.Router();

// Public routes
router.post('/register', registerUser);
router.post('/login', loginUser);

router.use(protect);

// Protected routes (require authentication)
router.get('/profile/:id', getUserProfile);
router.put('/profile/:id', updateUserProfile);
router.delete('/profile/:id', deleteUserAccount);

export default router;