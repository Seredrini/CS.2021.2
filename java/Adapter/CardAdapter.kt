package com.example.myapplication.Adapter

import android.content.Context
import android.content.Intent
import android.content.Intent.FLAG_ACTIVITY_NEW_TASK
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.chauthai.swipereveallayout.SwipeRevealLayout
import com.chauthai.swipereveallayout.ViewBinderHelper
import com.example.myapplication.*
import com.example.myapplication.DataBase.DBCall
import com.example.myapplication.Entity.Training

class CardAdapter(private var list: List<Training>?, val context: Context) : RecyclerView.Adapter<CardAdapter.ViewHolder>(){

    private val viewBinderHelper = ViewBinderHelper()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.card, parent, false)
        return ViewHolder(itemView)
    }

    override fun getItemCount() = list?.size ?: 0

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {

        var currentItem : Training? = null
        if (list != null) {
            currentItem = list!![position]
        }

        viewBinderHelper.setOpenOnlyOne(true)
        if (currentItem != null) {
            viewBinderHelper.bind(holder.layout, currentItem.name)
            viewBinderHelper.closeLayout(currentItem.name)
            holder.textView.text = currentItem.name
        }


        val db_call = DBCall(context)

        //редактировать тренировку
        holder.edit.setOnClickListener{
            val i = Intent(context, CreateTrainingActivity::class.java)
            i.addFlags(FLAG_ACTIVITY_NEW_TASK);
            if (currentItem != null) {
                i.putExtra("id", currentItem.ID_Training)
                viewBinderHelper.closeLayout(currentItem.name)
            }
            context.startActivity(i)
        }

        //удалить тренировку
        holder.delete.setOnClickListener{
            list = db_call.deleteTraining(currentItem)
            if (currentItem != null) {
                viewBinderHelper.closeLayout(currentItem.name)
            }
            notifyDataSetChanged()
        }


        //  начать тренировку
        holder.textView.setOnClickListener{
            val j = Intent(context, TrainingProcessActivity::class.java)
            j.addFlags(FLAG_ACTIVITY_NEW_TASK);
            if (currentItem != null) {
                j.putExtra("id", currentItem.ID_Training)
            }
            val no_appr : Boolean = db_call.isThereNoAppr(currentItem?.ID_Training!!)
            if (no_appr){
                //вызываем диалоговое окно
                val dialog = WarningDialogFragment()
                val activity = holder.itemView.context as? TrainingListActivity
                val manager = activity?.supportFragmentManager
                if (manager != null) {
                    dialog.show(manager, "warning")
                }
            } else{
                context.startActivity(j)
            }
        }
    }

    class ViewHolder(itemView: View): RecyclerView.ViewHolder(itemView){
        val textView: TextView = itemView.findViewById(R.id.tr_name)
        val edit: ImageView = itemView.findViewById(R.id.img_edit)
        val delete: ImageView = itemView.findViewById(R.id.img_delete)
        val layout : SwipeRevealLayout = itemView.findViewById(R.id.swipe_layout)
    }

    fun delete(position: Int){
        var currentItem : Training? = null
        if (list != null) {
            currentItem = list!![position]
        }
        val db_call = DBCall(context)
        list = db_call.deleteTraining(currentItem)
        notifyDataSetChanged()
    }
}