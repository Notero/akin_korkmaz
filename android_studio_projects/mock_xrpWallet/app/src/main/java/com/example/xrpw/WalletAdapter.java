package com.example.xrpw;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.ListAdapter;
import androidx.recyclerview.widget.RecyclerView;

public class WalletAdapter extends ListAdapter<Wallet, WalletAdapter.WalletViewHolder> {

    public interface OnWalletClickListener {
        void onWalletClick(Wallet wallet);

        void onWalletLongClick(Wallet wallet);
    }

    private final OnWalletClickListener listener;

    public WalletAdapter(OnWalletClickListener listener) {
        super(DIFF_CALLBACK);
        this.listener = listener;
    }

    private static final DiffUtil.ItemCallback<Wallet> DIFF_CALLBACK = new DiffUtil.ItemCallback<Wallet>() {
        @Override
        public boolean areItemsTheSame(@NonNull Wallet oldItem, @NonNull Wallet newItem) {
            return oldItem.getId() == newItem.getId();
        }

        @Override
        public boolean areContentsTheSame(@NonNull Wallet oldItem, @NonNull Wallet newItem) {
            return oldItem.getName().equals(newItem.getName())
                    && oldItem.getKeys().equals(newItem.getKeys());
        }
    };

    @NonNull
    @Override
    public WalletViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.wallet, parent, false);
        return new WalletViewHolder(v);
    }

    @Override
    public void onBindViewHolder(@NonNull WalletViewHolder holder, int position) {
        final Wallet wallet = getItem(position);
        holder.tvWalletTitle.setText(wallet.getName());
        holder.tvWalletKeys.setText(wallet.getKeys());

        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (listener != null) {
                    listener.onWalletClick(wallet);
                }
            }
        });

        holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                if (listener != null) {
                    listener.onWalletLongClick(wallet);
                    return true;
                }
                return false;
            }
        });
    }

    static class WalletViewHolder extends RecyclerView.ViewHolder {

        TextView tvWalletTitle;
        TextView tvWalletKeys;

        public WalletViewHolder(@NonNull View itemView) {
            super(itemView);
            tvWalletTitle = itemView.findViewById(R.id.tvWalletTitle);
            tvWalletKeys = itemView.findViewById(R.id.tvWalletKeys);
        }
    }
}
