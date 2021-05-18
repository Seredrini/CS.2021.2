package com.example.myapplication

import android.app.AlertDialog
import android.app.Dialog
import android.os.Bundle
import androidx.fragment.app.DialogFragment


class WarningDialogFragment : DialogFragment() {


    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        val builder: AlertDialog.Builder = AlertDialog.Builder(activity)
        return builder
            .setTitle("Нельзя начать тренировки")
            .setIcon(R.drawable.ic_baseline_report_problem_24)
            .setMessage("Для проведения тренировки введите упражнения и подходы")
            .setPositiveButton("OK", null)
            .create();

    }


}