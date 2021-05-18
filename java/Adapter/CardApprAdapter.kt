package com.example.myapplication.Adapter

import android.content.Context
import android.text.Editable
import android.text.TextWatcher
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.chauthai.swipereveallayout.SwipeRevealLayout
import com.chauthai.swipereveallayout.ViewBinderHelper
import com.example.myapplication.ApproachListActivity
import com.example.myapplication.DataBase.DBCall
import com.example.myapplication.Entity.Approach
import com.example.myapplication.R


class CardApprAdapter(var id:Int, val context: Context) : RecyclerView.Adapter<CardApprAdapter.ViewHolder>() {

    val db_call = DBCall(context)
    var list: List<Approach>? = db_call.getAllApprFromEx(id)
    private val viewBinderHelper = ViewBinderHelper()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.approach_card, parent, false)
        return ViewHolder(itemView)
    }

    override fun getItemCount() = list?.size ?: 0

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        var currentItem: Approach? = null
        currentItem = list?.get(position)
        val st: String = "Подход " + (position+1).toString()

        viewBinderHelper.setOpenOnlyOne(true)
        if (currentItem != null) {
            viewBinderHelper.bind(holder.layout, st)
            viewBinderHelper.closeLayout(st)
            holder.number.text = st
        }


        if (holder.repeat.length() != 0){
            if (currentItem != null) {
                currentItem.repeat = holder.repeat.text.toString().toInt()
                db_call.addApprToEx(currentItem)
            }
        }
        else{
            holder.repeat.text = currentItem?.repeat?.toString() ?: list?.get(0)?.repeat?.toString() ?: ""
        }
        if (holder.weight.length() != 0){
            if (currentItem != null) {
                currentItem.weight = holder.weight.text.toString().toInt()
                db_call.addApprToEx(currentItem)
            }
        }
        else{
            holder.weight.text = currentItem?.weight?.toString() ?: list?.get(0)?.weight?.toString() ?: ""
        }


        //удалить подход
        holder.delete.setOnClickListener{
            db_call.deleteApprFromEx(currentItem)
            list = db_call.getAllApprFromEx(id)
            viewBinderHelper.closeLayout(st)
            notifyDataSetChanged()
        }

    }


    class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val number: TextView = itemView.findViewById(R.id.appr_number)
        val weight: TextView = itemView.findViewById(R.id.weight)
        val repeat: TextView = itemView.findViewById(R.id.repeat)
        val delete: ImageView = itemView.findViewById(R.id.img_delete)
        val layout : SwipeRevealLayout = itemView.findViewById(R.id.swipe_layout)
    }


    fun addNewApp(){
        notifyDataSetChanged()
        val appr = Approach(null, id, null, null)
        db_call.addApprToEx(appr)
        list = db_call.getAllApprFromEx(id)
    }

}