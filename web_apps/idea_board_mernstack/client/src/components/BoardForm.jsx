import React, { useState } from 'react';
import api from '../api/utils/axios';

const BoardModal = () => {
  const [formData, setFormData] = useState({
    name: '',
    description: '',
  });

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  // Custom function to handle submission and close modal
  const handleSubmit = async (e) => {
    e.preventDefault();

    console.log("Saving Board...", formData);

    try {
      await api.post('/board', formData);
      
      // Clear form
      setFormData({ name: '', description: '' });
      
      // Close modal
      document.getElementById('board_modal').close();

      // Refresh the page or trigger a re-fetch of boards
      window.location.reload(); 
    } catch (error) {
      console.error("Error creating board:", error);
    }
  };

  return (
    <>
      {/* 2. The Modal Window */}
      <dialog id="board_modal" className="modal modal-bottom sm:modal-middle">
        <div className="modal-box bg-base-100 border border-base-300">
          
          {/* Close Button (top right) */}
          <form method="dialog">
            <button className="btn btn-sm btn-circle btn-ghost absolute right-2 top-2">✕</button>
          </form>

          <h3 className="font-bold text-lg mb-4 text-primary text-center">Create New Board</h3>

          {/* 3. The Form Content */}
          <form onSubmit={handleSubmit} className="space-y-4">
            <div className="form-control">
              <input 
                type="text" 
                name="name"
                value={formData.name}
                onChange={handleChange}
                placeholder="Board Name" 
                className="input input-bordered w-full" 
                required 
              />
            </div>

            <div className="form-control">
              <textarea 
                name="description"
                value={formData.description}
                onChange={handleChange}
                className="textarea textarea-bordered w-full h-32" 
                placeholder="Board Description"
                required
              ></textarea>
            </div>

            <div className="modal-action">
              <button type="submit" className="btn btn-primary w-full">Create Board</button>
            </div>
          </form>
        </div>

        {/* 4. The Overlay (Clicking outside closes it) */}
        <form method="dialog" className="modal-backdrop">
          <button>close</button>
        </form>
      </dialog>
    </>
  );
};

export default BoardModal;