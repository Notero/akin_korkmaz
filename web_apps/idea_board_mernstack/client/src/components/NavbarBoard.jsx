import { ArrowBigLeft, PlusIcon } from 'lucide-react'
import { Link } from 'react-router'

const NavbarBoard = () => {
    return (

        <div>
            <div className="navbar bg-base-100 shadow-sm">
                <div className="flex-1">
                    <a className="btn btn-ghost text-xl">Idea Board</a>
                </div>
                <div className="flex-none">
                    <button className="btn btn-square btn-ghost" onClick={() => document.getElementById('idea_modal').showModal()}>
                        <PlusIcon className="size-5" />
                    </button>

                    <button className="btn btn-square btn-ghost">
                        <Link to="/">
                            <ArrowBigLeft className="size-5" />
                        </Link>
                    </button>

                </div>
            </div>
        </div>
    )
}

export default NavbarBoard
