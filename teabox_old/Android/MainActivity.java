package com.example.teabox;

import static com.example.teabox.utils.NetworkUtils.generateURL;
import static com.example.teabox.utils.NetworkUtils.getResponseFromURL;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.AsyncTask;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.net.URL;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity {

    private TextView result;
    private static String LedState = "";
    private static final String LED_STATUS = "Led Status";
    LedQueryUpdate test = new LedQueryUpdate();
    URL generatedBaseURL = generateURL("");


    //==================================================================================================================================
    @SuppressLint("StaticFieldLeak")
    class LedQueryTask extends AsyncTask<URL, Void, String> {

        @Override
        protected String doInBackground(URL... urls) {

            System.out.println("Debug in LedQueryTask_Back_1: " + urls[0].toString());

            String response = null;
            try {
                response = getResponseFromURL(urls[0]);
            } catch (IOException e) {
                e.printStackTrace();
            }

            System.out.println("Debug in LedQueryTask_Back_2: " + response);

            return response;
        }

        @Override
        protected void onPostExecute(String response) {
            System.out.println("Debug in LedQueryTask_Post: " + response);
            LedState = response;
            String result_str;
            if(response == null || response.equals("")) {
                result_str = LED_STATUS;
            } else {
                result_str = LED_STATUS + ": " + LedState;
            }
            result.setText(result_str);
        }
    }

//==================================================================================================================================
@SuppressLint("StaticFieldLeak")
class LedQueryUpdate extends AsyncTask<URL, String, String> {

        @Override
        protected String doInBackground(URL... urls) {
            System.out.println("Debug in LedQueryUpdate_Back_1: " + urls[0].toString());
            String response = "";



            while (!isCancelled()) {

                try {
                    response = getResponseFromURL(urls[0]);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if(response == null || response.equals(""))

                System.out.println("Debug in LedQueryTask_Back_3: " + response);

                publishProgress(response);



                try {
                    TimeUnit.SECONDS.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

            }

            return "";
        }

        @Override
        protected void onProgressUpdate(String... values) {
            String response = values[0];
            LedState = response;
            String result_str;
            if(response == null || response.equals("")) {
                result_str = LED_STATUS;
            } else {
                result_str = LED_STATUS + ": " + LedState;
            }
            result.setText(result_str);
        }

        @Override
        protected void onPostExecute(String response) {
            System.out.println("Debug in LedQueryUpdate_Post_2: " + response);
            LedState = response;
            String result_str;
            if(response == null || response.equals("")) {
                result_str = LED_STATUS;
            } else {
                result_str = LED_STATUS + ": " + LedState;
            }
            result.setText(result_str);
        }

    @Override
    protected void onCancelled() {
        super.onCancelled();
        System.out.println("Debug in LedQueryUpdate_3: " +  "Cancel");
    }
}

//==================================================================================================================================
    @Override
    protected void onCreate(Bundle savedInstanceState)  {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        test.execute(generatedBaseURL);


        try {
            addListenerButton();
        } catch (IOException e) {
            e.printStackTrace();
        }



    }

//==================================================================================================================================
    public void addListenerButton() throws IOException{

        Button switcher = findViewById(R.id.button_switch);
        result = findViewById(R.id.text_result);

        switcher.setOnClickListener(
                view -> {
                    System.out.println("Debug in button click_1: " + LedState);


                    test.cancel(false);


                    String New_LedState = LedState;

                    if(LedState.equals("ON")) {
                        New_LedState = "ledoff";
                    } else if(LedState.equals("OFF")) {
                        New_LedState = "ledon";
                    }

                    System.out.println("Debug in button click_2: " + New_LedState);

                    URL generatedURL = generateURL(New_LedState);

                    System.out.println("Debug in button click_3: " + generatedURL);

                    new LedQueryTask().execute(generatedURL);
                    System.out.println("Debug in button click_4: " + LedState);



                    System.out.println("Debug in button click_5: " + generatedBaseURL);
                    test = null;
                    test = new LedQueryUpdate();
                    test.execute(generatedBaseURL);

                }

        );

    }

}