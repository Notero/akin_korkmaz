import React, { useState } from 'react';
import LoginCard from '../components/LoginCard';
import { useNavigate } from 'react-router';
import api from '../api/utils/axios';
import toast from 'react-hot-toast';


const LoginPage = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const navigate = useNavigate();

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await api.post('/user/login', { email, password });

      if (response.status === 200) {
        toast.success('Login successful!');
        navigate('/dashboard');
      }
    } catch (error) {
      if (error.response) {
        toast.error(error.response.data.message || 'Login failed');
      } else {
        toast.error('Network error or server is down');
      }
      console.error('Login failed:', error);
    }
  };

  return (
    /* 2. Use DaisyUI 'hero' to handle the centering and background */
    <div 
      className="hero min-h-screen"
    >
      {/* 3. This overlay ensures your LoginCard is readable over the PNG */}
      <div className="hero-overlay bg-opacity-40 backdrop-blur-sm"></div>
      
      <div className="hero-content text-center">
        <LoginCard 
          email={email} 
          setEmail={setEmail}
          password={password}
          setPassword={setPassword}
          handleSubmit={handleSubmit}
        />
      </div>
    </div>
  );
};

export default LoginPage;