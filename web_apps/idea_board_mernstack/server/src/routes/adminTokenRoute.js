import express from 'express';
import { generateAdminToken } from '../controllers/adminToken.js';

const router = express.Router();

// Route to generate a new admin token
router.get('/create', generateAdminToken);

export default router;