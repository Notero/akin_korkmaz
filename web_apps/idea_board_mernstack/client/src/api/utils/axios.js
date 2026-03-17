import axios from 'axios';

const api = axios.create({  // Use your environment variable or the hardcoded string
  baseURL: `http://localhost:8001/api`,
  // Cookies
  withCredentials: true, 
  headers: {
    'Content-Type': 'application/json',
  },
});

export default api;