package com.example.myapplication.Adapter

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Typeface
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.BaseExpandableListAdapter
import android.widget.TextView
import com.example.myapplication.DataBase.DBCall
import com.example.myapplication.Entity.ExerciseList
import com.example.myapplication.Entity.Muscle
import com.example.myapplication.R

class CustomExpandableListAdapter internal constructor(private val context: Context,
                                                       val id: Int
                                    ) : BaseExpandableListAdapter() {

    val db_call = DBCall(this.context)
    val list: List<List<ExerciseList>> = db_call.getListData()
    val muscle : List<Muscle>? = db_call.getMuscle()
    var oldlist : List <ExerciseList> = db_call.getAllExListByTraining(id)

    override fun getChild(listPosition: Int, expandedListPosition: Int): Any {
        return list[listPosition][expandedListPosition]

    }

    override fun getChildId(listPosition: Int, expandedListPosition: Int): Long {
        return expandedListPosition.toLong()
    }

    @SuppressLint("ResourceAsColor")
    override fun getChildView(listPosition: Int, expandedListPosition: Int, isLastChild: Boolean, convertView: View?, parent: ViewGroup): View {
        var convertView = convertView
        val expandedList = getChild(listPosition, expandedListPosition) as ExerciseList
        if (convertView == null) {
            val layoutInflater = this.context.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater
            convertView = layoutInflater.inflate(R.layout.list_element, null)
        }
        val expandedListTextView = convertView!!.findViewById<TextView>(R.id.el)
        expandedListTextView.text = expandedList.name

        if ( oldlist.contains(expandedList) ){
            expandedListTextView.setBackgroundResource(R.color.light_blue)
        }
        else{
            expandedListTextView.setBackgroundResource(R.color.white)
        }




        expandedListTextView.setOnClickListener {
            Log.d("Outer Pos", listPosition.toString())
            Log.d("Inner Pos", expandedListPosition.toString())
            if (oldlist.contains(expandedList) ){
                db_call.deleteExListFromTraining(expandedList.ID_ExList, id)
                expandedListTextView.setBackgroundResource(R.color.white)
            }
            else{
                db_call.addExToTraining(expandedList.ID_ExList, id)
                expandedListTextView.setBackgroundResource(R.color.light_blue)
            }
            oldlist = db_call.getAllExListByTraining(id)
            notifyDataSetChanged()
        }

        return convertView
    }



    override fun getChildrenCount(listPosition: Int): Int {
        return list[listPosition].size
    }

    override fun getGroup(listPosition: Int): String? {
        return muscle?.get(listPosition)?.name
    }

    override fun getGroupCount(): Int {
        if (muscle != null) {
            return muscle.size
        } else{
            return 0
        }
    }

    override fun getGroupId(listPosition: Int): Long {
        return listPosition.toLong()
    }

    override fun getGroupView(listPosition: Int, isExpanded: Boolean, convertView: View?, parent: ViewGroup): View {
        var convertView = convertView
        val listTitle = getGroup(listPosition) as String
        if (convertView == null) {
            val layoutInflater = this.context.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater
            convertView = layoutInflater.inflate(R.layout.list_element, null)
        }
        val listTitleTextView = convertView!!.findViewById<TextView>(R.id.el)
        listTitleTextView.setTypeface(null, Typeface.BOLD)
        listTitleTextView.text = listTitle
        return convertView
    }

    override fun hasStableIds(): Boolean {
        return false
    }

    override fun isChildSelectable(listPosition: Int, expandedListPosition: Int): Boolean {
        return true
    }
}
