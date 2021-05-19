package com.example.myapplication.Adapter

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.chauthai.swipereveallayout.SwipeRevealLayout
import com.chauthai.swipereveallayout.ViewBinderHelper
import com.example.myapplication.ApproachListActivity
import com.example.myapplication.DataBase.DBCall
import com.example.myapplication.Entity.Exercise
import com.example.myapplication.R

class CardExAdapter( val id: Int, val context: Context) : RecyclerView.Adapter<CardExAdapter.ViewHolder>() {

    val db_call = DBCall(context)
    private var list : List<Exercise>? = db_call.getAllExByTraining(id)
    private val viewBinderHelper = ViewBinderHelper()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.card_ex, parent, false)
        return ViewHolder(itemView)
    }

    override fun getItemCount() = list?.size ?: 0

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        var currentItem : Exercise? = null
        currentItem = list?.get(position)
        val st = db_call.getExName(currentItem)

        viewBinderHelper.setOpenOnlyOne(true)
        if (currentItem != null) {
            viewBinderHelper.bind(holder.layout, st)
            viewBinderHelper.closeLayout(st)
            holder.textView.text = st
        }


        //удалить тренировку
        holder.delete.setOnClickListener{
            db_call.deleteExFromTraining(currentItem)
            list = db_call.getAllExByTraining(id)
            viewBinderHelper.closeLayout(st)
            notifyDataSetChanged()
        }

        //переход в подходы
        val i = Intent(context, ApproachListActivity::class.java)
        i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        holder.textView.setOnClickListener{
            i.putExtra("id", id)
            if (currentItem != null) {
                i.putExtra("ex_id", currentItem.ID_Ex)
            }
            context.startActivity(i)
        }
    }

    class ViewHolder(itemView: View): RecyclerView.ViewHolder(itemView){
        val textView: TextView = itemView.findViewById(R.id.tr_name)
        val delete: ImageView = itemView.findViewById(R.id.img_delete)
        val layout : SwipeRevealLayout = itemView.findViewById(R.id.swipe_layout)
    }
}