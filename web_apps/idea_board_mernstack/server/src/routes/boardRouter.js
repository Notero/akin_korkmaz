import express from 'express';
import { createBoard, updateBoard, deleteBoard, getAllBoards, getBoardById } from '../controllers/boardController.js';
import { protect } from '../middleware/jwtProtect.js';

const router = express.Router();

router.use(protect);
// authentication for these API endpoints - 
// all routes below this line will require
// a valid JWT token in the Authorization header when sending a request.
// If the token is missing or invalid, the middleware will respond with a 401 Unauthorized error,
// preventing access to the protected routes.

router.get("/", getAllBoards);
router.get("/:id", getBoardById);
router.post("/", createBoard);
router.put("/:id", updateBoard);
router.delete("/:id", deleteBoard);

export default router;