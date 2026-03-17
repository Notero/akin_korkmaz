import express from 'express';
import {createIdea,updateIdea,deleteIdea,getAllIdeas, getIdeaById} from '../controllers/ideaController.js';
import { protect } from '../middleware/jwtProtect.js';

const router = express.Router();

router.use(protect); 
// authentication for these API endpoints - 
// all routes below this line will require
// a valid JWT token in the Authorization header when sending a request.
// If the token is missing or invalid, the middleware will respond with a 401 Unauthorized error,
// preventing access to the protected routes.

router.get("/", getAllIdeas);
router.get("/:id", getIdeaById);
router.post("/", createIdea);
router.put("/:id", updateIdea);
router.delete("/:id", deleteIdea);

export default router;