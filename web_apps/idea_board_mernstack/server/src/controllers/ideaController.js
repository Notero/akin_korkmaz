import Idea from '../models/Idea.js';
import {asyncHandler} from '../utils/asyncHandler.js'; // Assuming you saved it here

// 1. Get All Ideas
export const getAllIdeas = asyncHandler(async (req, res) => {

    const ideas = await Idea.find({ board: req.query.board,user: req.user._id }).sort({ createdAt: -1 });

    res.status(200).json(ideas);
});

// 2. Get Single Idea
export const getIdeaById = asyncHandler(async (req, res) => {
    const idea = await Idea.findById(req.params.id).populate('user', 'username').populate('board', 'name');

    if (!idea) {
        res.status(404);
        throw new Error("Idea not found!");
    }

    res.status(200).json(idea);
});

// 3. Create Idea
export const createIdea = asyncHandler(async (req, res) => {
    const { title, description, tags, board } = req.body;
    
    // Using .create() is a cleaner shorthand for new Idea() + .save()
    const savedIdea = await Idea.create({ title, description, tags, user: req.user._id, board });
    
    res.status(201).json({ message: "Idea created successfully", idea: savedIdea });
});

// 4. Update Idea
export const updateIdea = asyncHandler(async (req, res) => {
    let idea = await Idea.findById(req.params.id);

    if (!idea) {
        res.status(404);
        throw new Error("Idea not found!");
    }

    // Check ownership
    if (idea.user.toString() !== req.user._id.toString()) {
        res.status(403); // Forbidden
        throw new Error("Not authorized to update this idea");
    }

    const updatedIdea = await Idea.findByIdAndUpdate(
        req.params.id,
        req.body, // You can pass req.body directly if fields match
        { new: true, runValidators: true } // runValidators ensures the schema rules still apply
    );

    res.status(200).json({ message: "Idea updated successfully", idea: updatedIdea });
});

// 5. Delete Idea
export const deleteIdea = asyncHandler(async (req, res) => {
    let idea = await Idea.findById(req.params.id);

    if (!idea) {
        res.status(404);
        throw new Error("Idea not found!");
    }

    // Check ownership
    if (idea.user.toString() !== req.user._id.toString()) {
        res.status(403); // Forbidden
        throw new Error("Not authorized to delete this idea");
    }

    await Idea.deleteOne({ _id: req.params.id });

    res.status(200).json({ message: "Idea deleted successfully" });
});