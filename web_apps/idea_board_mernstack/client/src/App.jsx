import React from 'react'
import { Route, Routes } from 'react-router'

import HomePage from './pages/HomePage'
import CreatePage from './pages/CreatePage'
import LoginPage from './pages/LoginPage'
import BoardPage from './pages/BoardPage'
import IdeaFormCard from './components/IdeaForm'

const App = () => {
  return (
    <div>
      <Routes>
        <Route path='/' element={< LoginPage/>} />
        <Route path='/create' element={<CreatePage />} />
        <Route path='/dashboard' element={<HomePage />} />
        <Route path='/board/:boardId' element={<BoardPage />} />
        <Route path='/idea' element={<IdeaFormCard />} />

      </Routes>

    </div>
  )
}

export default App
