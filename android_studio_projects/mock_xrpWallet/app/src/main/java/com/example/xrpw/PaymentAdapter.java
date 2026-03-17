package com.example.xrpw;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.ListAdapter;
import androidx.recyclerview.widget.RecyclerView;

public class PaymentAdapter extends ListAdapter<Payment, PaymentAdapter.PaymentViewHolder> {

    public interface OnPaymentDeleteListener {
        void onDelete(Payment payment);
    }

    private final OnPaymentDeleteListener deleteListener;

    public PaymentAdapter(OnPaymentDeleteListener deleteListener) {
        super(DIFF_CALLBACK);
        this.deleteListener = deleteListener;
    }

    private static final DiffUtil.ItemCallback<Payment> DIFF_CALLBACK = new DiffUtil.ItemCallback<Payment>() {
        @Override
        public boolean areItemsTheSame(@NonNull Payment oldItem, @NonNull Payment newItem) {
            return oldItem.getId() == newItem.getId();
        }

        @Override
        public boolean areContentsTheSame(@NonNull Payment oldItem, @NonNull Payment newItem) {
            return oldItem.getAmountText().equals(newItem.getAmountText())
                    && oldItem.getDestinationText().equals(newItem.getDestinationText())
                    && oldItem.getDateText().equals(newItem.getDateText());
        }
    };

    @NonNull
    @Override
    public PaymentViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_payment, parent, false);
        return new PaymentViewHolder(v);
    }

    @Override
    public void onBindViewHolder(@NonNull PaymentViewHolder holder, int position) {
        Payment p = getItem(position);
        holder.tvPaymentAmount.setText(p.getAmountText());
        holder.tvPaymentDestination.setText(p.getDestinationText());
        holder.tvPaymentDate.setText(p.getDateText());
        holder.btnDeletePayment.setOnClickListener(v -> deleteListener.onDelete(p));
    }

    static class PaymentViewHolder extends RecyclerView.ViewHolder {

        TextView tvPaymentAmount;
        TextView tvPaymentDestination;
        TextView tvPaymentDate;
        Button btnDeletePayment;

        public PaymentViewHolder(@NonNull View itemView) {
            super(itemView);
            tvPaymentAmount = itemView.findViewById(R.id.tvPaymentAmount);
            tvPaymentDestination = itemView.findViewById(R.id.tvPaymentDestination);
            tvPaymentDate = itemView.findViewById(R.id.tvPaymentDate);
            btnDeletePayment = itemView.findViewById(R.id.btnDeletePayment);
        }
    }
}
