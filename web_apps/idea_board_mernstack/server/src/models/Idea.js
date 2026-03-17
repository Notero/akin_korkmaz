import mongoose from "mongoose";

// 1- create schema
// 2- create model based on schema
// 3- export the model to be used in controllers

const ideaSchema = new mongoose.Schema({
    title: {
        type: String,
        required: true
    },
    description: {
        type: String,
        required: true
    },
    tags: {
        type: [String],
        default: []
    },
    user: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'User', // Reference to the User model
        required: true
    },
    board: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'Board', // Reference to the Board model
        required: true
    }
}, { timestamps: true });

const Idea = mongoose.model("Idea", ideaSchema);

export default Idea;