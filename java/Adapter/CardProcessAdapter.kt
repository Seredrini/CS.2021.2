package Adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.chauthai.swipereveallayout.SwipeRevealLayout
import com.chauthai.swipereveallayout.ViewBinderHelper
import com.example.myapplication.*
import com.example.myapplication.DataBase.DBCall
import com.example.myapplication.Entity.Exercise


class CardProcessAdapter( val id: Int, val context: Context) : RecyclerView.Adapter<CardProcessAdapter.ViewHolder>() {

    val db_call = DBCall(context)
    private var list : List<Exercise>? = db_call.getAllExByTraining(id)
    private var color_pos: Int = 0
    private val viewBinderHelper = ViewBinderHelper()
    val kol_appr_list = db_call.getApprKolListFromTr(id)
    var done_kol_appr_list = db_call.getDoneApprKolListFromTr(id)

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.card_process, parent, false)
        return ViewHolder(itemView)
    }

    override fun getItemCount() = list?.size ?: 0

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        var currentItem : Exercise? = null
        currentItem = list?.get(position)

        viewBinderHelper.setOpenOnlyOne(true)
        val st_name = db_call.getExName(currentItem)
        viewBinderHelper.bind(holder.layout, st_name)
        viewBinderHelper.closeLayout(st_name)

        holder.textView.text = db_call.getExName(currentItem)
        val kol_appr = kol_appr_list.get(position)
        val done_kol_appr = done_kol_appr_list.get(position)

        holder.done.text = done_kol_appr.toString()
        holder.kol.text = "/ " + kol_appr.toString()

        if (color_pos == position){
            holder.itemView.setBackgroundResource(R.color.light_blue)
        }
        else{
            holder.itemView.setBackgroundResource(R.color.light)
        }

        holder.info.setOnClickListener {
            val info: String? = currentItem?.let { it1 -> db_call.getDescFromEx(it1) }
            val dialog = TrInfoDialogFragment().newInstance(info)
            val activity = holder.itemView.context as? TrainingProcessActivity
            val manager = activity?.supportFragmentManager
            if (manager != null) {
                dialog.show(manager, "info")
            }
            viewBinderHelper.closeLayout(st_name)
        }

        holder.textView.setOnClickListener {
            changeColorOnPosition(position)
            val activity = holder.itemView.context as? TrainingProcessActivity

            //если упражнение уже выполнено
            if (done_kol_appr == kol_appr){
                if (activity != null) {
                    activity.exIsDone(position)
                }
            }

            //начинаем делать это упражнение
            else{
                if (activity != null) {
                    activity. beginEx(position, done_kol_appr)
                }
            }
        }
    }

    class ViewHolder(itemView: View): RecyclerView.ViewHolder(itemView){
        val textView: TextView = itemView.findViewById(R.id.tr_name)
        val kol: TextView = itemView.findViewById(R.id.kol_appr)
        val done: TextView = itemView.findViewById(R.id.done_appr)
        val info: ImageView = itemView.findViewById(R.id.img_info)
        val layout : SwipeRevealLayout = itemView.findViewById(R.id.swipe_layout)
    }

    fun changeColorOnPosition(ex_num: Int){
        color_pos = ex_num
        notifyDataSetChanged()
    }

    fun changeDoneKolAppr(position: Int){
        var kol: Int = done_kol_appr_list.get(position)
        kol += 1
        (done_kol_appr_list as ArrayList<Int>).set(position, kol)
        notifyDataSetChanged()
    }

    fun getDoneKolAppr(position: Int): Int{
        val kol: Int = done_kol_appr_list.get(position)
        return kol
    }

}