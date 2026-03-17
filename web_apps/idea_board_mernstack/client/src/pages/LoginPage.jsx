import React, { useState } from 'react';
import LoginCard from '../components/LoginCard';
import { useNavigate } from 'react-router';
import api from '../api/utils/axios';

// 1. Import the relative path correctly
import bgImage from '../../bgimage.png'; 

const LoginPage = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const navigate = useNavigate();

  const handleSubmit = async (e) => {
    e.preventDefault();
    // Handle login logic here (e.g., API call to authenticate user)
    console.log('Email:', email);
    console.log('Password:', password);
      try {
        //API CALL TO LOGIN USER
        const response = await api.post('/user/login', { email: email, password: password });

        if (response.status === 200) {
          console.log('Login successful:', response.data);
          // You can redirect the user to the home page or dashboard here
          navigate('/');
        } else {
          console.error('Login failed with status:', response.status);
        }
    }catch (error) {
      console.error('Login failed:', error);
      }
};

  return (
    /* 2. Use DaisyUI 'hero' to handle the centering and background */
    <div 
      className="hero min-h-screen" 
      style={{ 
        backgroundImage: `url(${bgImage})`,
      }}
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