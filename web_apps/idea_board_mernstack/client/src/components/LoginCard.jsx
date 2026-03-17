import React from 'react';

const LoginCard = ({ email, setEmail, password, setPassword, handleSubmit }) => {
  return (
    <div className="card w-96 bg-base-100 shadow-xl border border-base-300">
      <form onSubmit={handleSubmit} className="card-body gap-4 items-start text-left">
        <h2 className="card-title text-3xl font-bold mb-2">Login</h2>
        
        {/* Email Field */}
        <div className="form-control w-full">
          <label className="label px-0 justify-start">
            <span className="label-text font-bold text-md text-base-content">Email</span>
          </label>
          <input
            type="text"
            placeholder="Enter email"
            className="input input-bordered w-full"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            required
          />
        </div>

        {/* Password Field */}
        <div className="form-control w-full">
          <label className="label px-0 justify-start">
            <span className="label-text font-bold text-md text-base-content">Password</span>
          </label>
          <input
            type="password"
            placeholder="••••••••"
            className="input input-bordered w-full"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            required
          />
          <div className="mt-2">
            <a href="#" className="link link-hover text-sm opacity-70">Forgot password?</a>
          </div>
        </div>

        {/* Action Button */}
        <div className="card-actions w-full mt-4">
          <button type="submit" className="btn btn-secondary btn-block text-lg">
            Login
          </button>
        </div>
      </form>
    </div>
  );
};

export default LoginCard;