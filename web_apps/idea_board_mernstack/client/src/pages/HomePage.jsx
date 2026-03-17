import React from 'react'
import Navbar from '../components/Navbar'
import Drawer from '../components/Drawer'
import RateLimitedUI from '../components/RateLimitedUI'
import api from '../api/utils/axios'

const HomePage = () => {
    //ratelimit state for testing
  const [isRateLimited, setIsRateLimited] = React.useState(false);
  const [board, setBoard] = React.useState([]);
  const [loading, setLoading] = React.useState(true);

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
    
    return (
    <div className='min-h-screen'>
        <Navbar />
        {isRateLimited && <RateLimitedUI />}
        <div className="max-w-7xl mx-auto p-4 mt-6">
            {loading && <div className="text-center text-secondary">Loading boards...</div>}
            {!loading && board.length === 0 && <div className="text-center text-secondary">No boards found.</div>}
            {board.length > 0 && !isRateLimited && (
                <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-6">
                    {board.map((board) => (
                        <div key={board._id} className="card bg-base-100 shadow-md">
                            <div className="card-body">
                                <h2 className="card-title">{board.title}</h2>
                                <p>{board.description}</p>
                                <div className="card-actions justify-end">
                                    <button className="btn btn-primary">View Details</button>
                                </div>
                            </div>
                        </div>
                    ))}
                </div>
            )}
        </div>
    </div>
  ) 
}

export default HomePage
