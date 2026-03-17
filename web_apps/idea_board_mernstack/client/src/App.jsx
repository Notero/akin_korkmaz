import React from 'react'
import { Route, Routes } from 'react-router'

import HomePage from './pages/HomePage'
import Idea from './pages/Idea'
import CreatePage from './pages/CreatePage'
import LoginPage from './pages/LoginPage'
import BoardPage from './pages/BoardPage'
import './Pettable/pettable'

const App = () => {
  return (
    <div data-theme="abyss">
      <Routes>
        <Route path='/' element={<HomePage />} />
        <Route path='/idea/:id' element={<Idea />} />
        <Route path='/create' element={<CreatePage />} />
        <Route path='/login' element={<LoginPage />} />
        <Route path='/board/:boardId' element={<BoardPage />} />

      </Routes>

    </div>
  )
}

export default App
