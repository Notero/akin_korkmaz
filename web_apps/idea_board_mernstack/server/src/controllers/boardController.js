import Board from '../models/Board.js';
import {asyncHandler} from '../utils/asyncHandler.js';

// 1. Get All Idea Boards for the authenticated user
export const getAllBoards = asyncHandler(async (req, res) => {
    const boards = await Board.find({ user: req.user._id }).sort({ createdAt: -1 }); // Filter by the authenticated user's ID
    res.status(200).json(boards);
});

// 2. Get Single Idea Board
export const getBoardById = asyncHandler(async (req, res) => {
    const board = await Board.findById(req.params.id);

    if (!board) {
        res.status(404);
        throw new Error("Idea board not found!");
    }

    // Check ownership
    if (board.user.toString() !== req.user._id.toString()) {
        res.status(403); // Forbidden
        throw new Error("Not authorized to access this idea board");
    }

    res.status(200).json(board);
});

export const createBoard = asyncHandler(async (req, res) => {
    const { name, description } = req.body;
    
    const newBoard = await Board.create({ name, description, user: req.user._id });
    res.status(201).json({ message: "Idea board created successfully", board: newBoard });
});

export const updateBoard = asyncHandler(async (req, res) => {
    let board = await Board.findById(req.params.id);

    if (!board) {
        res.status(404);
        throw new Error("Idea board not found!");
    }

    // Check ownership
    if (board.user.toString() !== req.user._id.toString()) {
        res.status(403); // Forbidden
        throw new Error("Not authorized to update this idea board");
    }

    const updatedBoard = await Board.findByIdAndUpdate(
        req.params.id,
        req.body, // You can pass req.body directly if fields match
        { new: true, runValidators: true } // runValidators ensures the schema rules still apply
    );

    res.status(200).json({ message: "Idea board updated successfully", board: updatedBoard });
});

export const deleteBoard = asyncHandler(async (req, res) => {
    let board = await Board.findById(req.params.id);

    if (!board) {
        res.status(404);
        throw new Error("Idea board not found!");
    }

    // Check ownership
    if (board.user.toString() !== req.user._id.toString()) {
        res.status(403); // Forbidden
        throw new Error("Not authorized to delete this idea board");
    }

    await Board.deleteOne({ _id: req.params.id });

    res.status(200).json({ message: "Idea board deleted successfully" });
});