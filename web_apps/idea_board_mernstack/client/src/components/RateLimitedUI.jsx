import React from 'react'

const RateLimitedUI = () => {
    return (
        <div className="flex justify-end items-center py-1 pr-6 max-h-screen">
            <div className="alert alert-error w-full max-w-fit">
                <svg className="shrink-0 max-w-fit h-6" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                    <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M12 9v2m0 4v2m0-6a4 4 0 110-8 4 4 0 010 8zm0 0a8 8 0 100-16 8 8 0 000 16z" />
                </svg>
                <div>
                    <h3 className="font-bold">Rate Limit Exceeded</h3>
                    <div className="text-xs">You have made too many requests. Please wait a moment before trying again.</div>
                </div>
            </div>
        </div>
    )
}

export default RateLimitedUI
