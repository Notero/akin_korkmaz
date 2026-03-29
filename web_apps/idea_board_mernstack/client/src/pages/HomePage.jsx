import React from 'react'
import { useNavigate } from 'react-router'
import Navbar from '../components/Navbar'
import BoardModal from '../components/BoardForm'
import RateLimitedUI from '../components/RateLimitedUI'
import api from '../api/utils/axios'

const HomePage = () => {
    //ratelimit state for testing
  const [isRateLimited, setIsRateLimited] = React.useState(false);
  const [board, setBoard] = React.useState([]);
  const [loading, setLoading] = React.useState(true);
  const navigate = useNavigate();

  React.useEffect(() => {
        const fetchBoards = async () => {
            try { 
                const response = await api.get('/board');
                console.log(response.data);
                setBoard(response.data);
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
        fetchBoards();
    }, [])

    const getBoardDetails = (_id) => {
        navigate(`/board/${_id}`); // This sends the user to a dynamic URL
    }
    
    return (
    <div className='min-h-screen'>
        <Navbar />
        {isRateLimited && <RateLimitedUI />}
        <div className="max-w-7xl mx-auto p-4 mt-6">
            {loading && <div className="text-center text-secondary">Loading boards...</div>}
            {!loading && board.length === 0 && <div className="text-center text-secondary">No boards found.</div>}
            {board.length > 0 && !isRateLimited && (
                <div className="columns-1 sm:columns-2 md:columns-3 lg:columns-4 gap-6">
                    {board.map((board) => (
                        <div key={board._id} className="card bg-base-300 shadow-md break-inside-avoid mb-6">
                            <div className="card-body">
                                <h2 className="card-title text-primary">{board.name}</h2>
                                <p className="text-secondary">{board.description}</p>
                                <div className="card-actions justify-end">
                                    <button className="btn btn-accentt" onClick={() => getBoardDetails(board._id)}>View Details</button>
                                </div>
                            </div>
                        </div>
                    ))}
                </div>
            )}
        </div>
        <BoardModal />
    </div>
  ) 
}

export default HomePage
