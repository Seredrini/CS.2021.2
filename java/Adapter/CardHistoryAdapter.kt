package Adapter

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
import com.example.myapplication.CreateTrainingActivity
import com.example.myapplication.DataBase.DBCall
import com.example.myapplication.Entity.Efficiency
import com.example.myapplication.R
import com.example.myapplication.TrainingProcessActivity


class CardHistoryAdapter (val context: Context) : RecyclerView.Adapter<CardHistoryAdapter.ViewHolder>() {

    val db_call = DBCall(context)
    private var list : List<Efficiency>? = db_call.getAllEffency()
    private val viewBinderHelper = ViewBinderHelper()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.card_history, parent, false)
        return ViewHolder(itemView)
    }

    override fun getItemCount() = list?.size ?: 0

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        var currentItem : Efficiency? = null
        currentItem = list?.get(position)

        viewBinderHelper.setOpenOnlyOne(true)

        val st_name = db_call.getTrNameByEff(currentItem)
        viewBinderHelper.bind(holder.layout, st_name)
        viewBinderHelper.closeLayout(st_name)

        holder.name.text = db_call.getTrNameByEff(currentItem)
        holder.date.text = db_call.getDateByEff(currentItem)
        holder.time.text = currentItem?.Time.toString() + " минут"
        val st: String = currentItem?.Percenr.toString() + "%"
        holder.percent.text = st

        //редактировать тренировку
        holder.edit.setOnClickListener{
            val i = Intent(context, CreateTrainingActivity::class.java)
            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            if (currentItem != null) {
                i.putExtra("id", currentItem.Training_ID)
            }
            viewBinderHelper.closeLayout(st_name)
            context.startActivity(i)
        }

        //начать тренировку
        holder.begin.setOnClickListener{
            val i = Intent(context, TrainingProcessActivity::class.java)
            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            if (currentItem != null) {
                i.putExtra("id", currentItem.Training_ID)
            }
            context.startActivity(i)
        }

        //удалить тренировку
        holder.delete.setOnClickListener{
            db_call.deleteEff(currentItem)
            update()
        }

    }

    class ViewHolder(itemView: View): RecyclerView.ViewHolder(itemView){
        val name: TextView = itemView.findViewById(R.id.tr_name)
        val date: TextView = itemView.findViewById(R.id.dat)
        val time: TextView = itemView.findViewById(R.id.time)
        val percent : TextView = itemView.findViewById(R.id.percent)
        val edit: ImageView = itemView.findViewById(R.id.img_edit)
        val begin: ImageView = itemView.findViewById(R.id.img_begin)
        val delete: ImageView = itemView.findViewById(R.id.img_delete)
        val layout : SwipeRevealLayout = itemView.findViewById(R.id.swipe_layout)
    }

    fun update(){
        list = db_call.getAllEffency()
        notifyDataSetChanged()
    }


}