import api from './utils/axios';

export const login = async (email, password) => {
  // Your backend will respond with a 'Set-Cookie' header
  return await api.post('/user/login', { email, password });
};

export const logout = async () => {
  // Your backend should clear the cookie on its end
  return await api.post('/user/logout');
};

export const checkAuthStatus = async () => {
  // A simple endpoint to see if the user's cookie is still valid
  return await api.get('/user/me'); 
};