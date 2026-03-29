import React from 'react'
import { useParams } from 'react-router'
import NavbarBoard from '../components/NavbarBoard'
import RateLimitedUI from '../components/RateLimitedUI'
import IdeaModal from '../components/IdeaForm'
import IdeaUpdateModal from '../components/IdeaFormUpdate'
import api from '../api/utils/axios'

const BoardPage = () => {
    const { boardId } = useParams();
    //ratelimit state for testing
  const [isRateLimited, setIsRateLimited] = React.useState(false);
  const [idea, setIdea] = React.useState([]);
  const [loading, setLoading] = React.useState(true);
  const [editingIdea, setEditingIdea] = React.useState(null);

  React.useEffect(() => {
        const fetchIdeas = async () => {
            try { 
                const response = await api.get(`/idea?board=${boardId}`);
                console.log(response.data);
                setIdea(response.data);
                setIsRateLimited(false);
                setLoading(false);
            }catch (error) {
                console.error('Error fetching boards:', error);
                if (error.response && error.response.status === 429) {
                    setIsRateLimited(true);
                }
            } finally {
                    setLoading(false);
                }
        };
        fetchIdeas();
    }, [boardId])

    const onDeleteIdea = async (ideaId) => {
        try {
            await api.delete(`/idea/${ideaId}`);
            setIdea(prevIdeas => prevIdeas.filter(idea => idea._id !== ideaId));
        } catch (error) {
            console.error('Error deleting idea:', error);
        }
    };
    
    return (
    <div className='min-h-screen'>
        <NavbarBoard />
        {isRateLimited && <RateLimitedUI />}
        <div className="max-w-7xl mx-auto p-4 mt-6">
            {loading && <div className="text-center text-secondary">Loading boards...</div>}
            {!loading && idea.length === 0 && <div className="text-center text-secondary">No boards found.</div>}
            {idea.length > 0 && !isRateLimited && (
                <div className="columns-1 sm:columns-2 md:columns-3 lg:columns-4 gap-6">
                    {idea.map((idea) => (
                        <div key={idea._id} className="card bg-base-200 shadow-md break-inside-avoid mb-6">
                            <div className="card-body text-primary overflow-hidden">
                                
                                <h2 className="card-title break-words">{idea.title}</h2>
                                <p className='text-secondary break-words'>{idea.description}</p>
                                <button className="btn btn-error" onClick={() => onDeleteIdea(idea._id)}>delete</button>
                                <button className="btn btn-accent" onClick={() => {
                                    setEditingIdea(idea);
                                    document.getElementById('idea_update_modal').showModal();
                                }}>edit</button>
                            </div>
                        </div>
                    ))}
                </div>
            )}
        </div>
        <IdeaModal />
        <IdeaUpdateModal 
            ideaToEdit={editingIdea} 
            onClose={() => {
                setEditingIdea(null);
                document.getElementById('idea_update_modal').close();
            }} 
        />
    </div>
  ) 
}

export default BoardPage