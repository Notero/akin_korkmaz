import React, { useState, useEffect } from 'react';
import api from '../api/utils/axios';
import { useParams } from 'react-router';

// We pass the currently selected idea down as a prop so we can pre-fill the form
const IdeaUpdateModal = ({ ideaToEdit, onClose }) => {
  const { boardId } = useParams();

  const [formData, setFormData] = useState({
    title: '',
    description: '',
    tags: '',
  });

  // When the modal opens or the ideaToEdit changes, pre-fill the form
  useEffect(() => {
    if (ideaToEdit) {
      setFormData({
        title: ideaToEdit.title || '',
        description: ideaToEdit.description || '',
        tags: ideaToEdit.tags ? ideaToEdit.tags.join(', ') : '', // Assuming tags is an array from the backend
      });
    }
  }, [ideaToEdit]);

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  // Custom function to handle submission and close modal
  const handleSubmit = async (e) => {
    e.preventDefault();
    
    const payload = {
      ...formData,
      board: boardId
    };

    // If tags is sent as a comma separated string, we can convert it to an array
    if (typeof payload.tags === 'string' && payload.tags.length > 0) {
      payload.tags = payload.tags.split(',').map(tag => tag.trim());
    }

    console.log("Updating Idea...", payload);

    try {
      // Use PUT and append the specific idea's ID to the URL
      await api.put(`/idea/${ideaToEdit._id}`, payload);
      
      // Close modal by calling the onClose prop passed from the parent
      onClose();

      // Refresh the page or trigger a re-fetch of ideas
      window.location.reload(); 
    } catch (error) {
      console.error("Error updating idea:", error);
    }
  };

  return (
    <>
      <dialog id="idea_update_modal" className="modal modal-bottom sm:modal-middle">
        <div className="modal-box bg-base-100 border border-base-300">
          
          <form method="dialog">
            {/* We call onClose when clicking the X to clear the selected idea state in the parent */}
            <button className="btn btn-sm btn-circle btn-ghost absolute right-2 top-2" onClick={onClose}>✕</button>
          </form>

          <h3 className="font-bold text-lg mb-4 text-primary text-center">Edit Idea</h3>

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
              <button type="submit" className="btn btn-primary w-full">Update Idea</button>
            </div>
          </form>
        </div>

        <form method="dialog" className="modal-backdrop">
          <button onClick={onClose}>close</button>
        </form>
      </dialog>
    </>
  );
};

export default IdeaUpdateModal;