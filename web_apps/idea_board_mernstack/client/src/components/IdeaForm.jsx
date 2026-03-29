import React, { useState } from 'react';
import api from '../api/utils/axios';
import { useParams } from 'react-router';

const IdeaModal = () => {
  const { boardId } = useParams();

  const [formData, setFormData] = useState({
    title: '',
    description: '',
    tags: '',
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
    
    // We append the board ID from the URL to the data being sent
    const payload = {
      ...formData,
      board: boardId
    };

    console.log("Saving Idea...", payload);

    try {
      await api.post('/idea', payload);
      
      // Clear form
      setFormData({ title: '', description: '', tags: '' });
      
      // Close modal
      document.getElementById('idea_modal').close();

      // Refresh the page or trigger a re-fetch of ideas
      window.location.reload(); 
    } catch (error) {
      console.error("Error creating idea:", error);
    }
  };

  return (
    <>
      {/* 2. The Modal Window */}
      <dialog id="idea_modal" className="modal modal-bottom sm:modal-middle">
        <div className="modal-box bg-base-100 border border-base-300">
          
          {/* Close Button (top right) */}
          <form method="dialog">
            <button className="btn btn-sm btn-circle btn-ghost absolute right-2 top-2">✕</button>
          </form>

          <h3 className="font-bold text-lg mb-4 text-primary text-center">Add New Idea</h3>

          {/* 3. The Form Content */}
          <form onSubmit={handleSubmit} className="space-y-4">
            <div className="form-control">
              <input 
                type="text" 
                name="title"
                value={formData.title}
                onChange={handleChange}
                placeholder="Idea Title" 
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
                placeholder="Description"
                required
              ></textarea>
            </div>

            <div className="form-control">
              <input 
                type="text" 
                name="tags"
                value={formData.tags}
                onChange={handleChange}
                placeholder="Tags (comma separated)" 
                className="input input-bordered w-full" 
              />
            </div>

            <div className="modal-action">
              <button type="submit" className="btn btn-primary w-full">Create Idea</button>
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

export default IdeaModal;