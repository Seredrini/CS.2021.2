package com.example.myapplication

import android.app.AlertDialog
import android.app.Dialog
import android.os.Bundle
import androidx.fragment.app.DialogFragment


class TrInfoDialogFragment : DialogFragment() {
    private var desc: String? = null

    fun newInstance(desc: String?): TrInfoDialogFragment {
        val f = TrInfoDialogFragment()
        val args = Bundle()
        args.putString("desc", desc)
        f.setArguments(args)
        return f
    }

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        arguments?.let {
            desc = it.getString("desc")

        }
        val builder: AlertDialog.Builder = AlertDialog.Builder(activity)
        return builder
            .setTitle("Техника выполнения упражнения")
            .setIcon(R.drawable.ic_fitness)
            .setMessage(desc)
            .setPositiveButton("OK", null)
            .create();

    }
}