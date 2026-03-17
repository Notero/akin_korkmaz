import { PlusIcon } from 'lucide-react'
import { Link } from 'react-router'

const Navbar = () => {
    return (
        <div>
            <div className="navbar bg-base-100 shadow-sm">
                <div className="flex-none">
                    <div className="drawer">
                        <input id="my-drawer-1" type="checkbox" className="drawer-toggle" />
                        <div className="drawer-content">
                            <label htmlFor="my-drawer-1" className="btn drawer-button">
                                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" className="inline-block w-6 h-6 stroke-current"><path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M4 6h16M4 12h16M4 18h16"></path></svg>
                            </label>
                        </div>
                        <div className="drawer-side">
                            <label
                                htmlFor="my-drawer-1"
                                aria-label="close sidebar"
                                className="drawer-overlay"
                            ></label>
                            <ul className="menu bg-base-200 min-h-full w-80 p-4">
                                <li><a>Sidebar Item 1</a></li>
                                <li><a>Sidebar Item 2</a></li>
                            </ul>
                        </div>
                    </div>
                </div>
                <div className="flex-1">
                    <a className="btn btn-ghost text-xl">Idea Board</a>
                </div>
                <div className="flex-none">
                    <button className="btn btn-square btn-ghost">
                        <Link to="/create">
                            <PlusIcon className="size-5" />
                        </Link>
                    </button>
                </div>
            </div>
        </div>
    )
}

export default Navbar
