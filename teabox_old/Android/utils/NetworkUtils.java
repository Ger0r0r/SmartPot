package com.example.teabox.utils;

import android.net.Uri;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;

public class NetworkUtils {
    private static final String BASE_URL = "http://espcontrol.hopto.org";
    public  static final String FOR_FIND = "LED Status: ";

//==================================================================================================================================

    public static URL generateURL (String ledState) {
        System.out.println("Debug in generateURL: " + ledState);
        Uri builtUri = Uri.parse(BASE_URL + "/" + ledState);

        System.out.println("Debug in generateUrl_2: " + builtUri.toString());

        URL url = null;
        try {
            url = new URL(builtUri.toString());
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }

        System.out.println("Debug in generateUrl_3: " + url);
        return url;
    }

//==================================================================================================================================

    public static String getResponseFromURL (URL url) throws IOException {

        System.out.println("Debug in getResponseFromURL_1: " + url);

        HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();

        System.out.println("Debug in getResponseFromURL_2: " + url);

        try {
            InputStream in = urlConnection.getInputStream();

            System.out.println("Debug in getResponseFromURL_3: " + url);

            Scanner scanner = new Scanner(in);
            scanner.useDelimiter("\\A");

            boolean hasInput = scanner.hasNext();
            if (hasInput) {

                System.out.println("Debug in getResponseFromURL_hasInput_1: " + "True");

                return getLedState(scanner.next());
            } else {

                System.out.println("Debug in getResponseFromURL_hasInput_1: " + "False");

                return null;
            }
        } finally {
            urlConnection.disconnect();
            System.out.println("Debug in getResponseFromURL_4: " + "finally");

        }
    }

//==================================================================================================================================

    public static String getLedState (String input_str) {

            int tmp  = input_str.indexOf(FOR_FIND) + FOR_FIND.length();
            String output_str = input_str.substring(tmp, tmp + 3);
            if(output_str.charAt(1) == 'N') {
                output_str = "ON";
            }

            return output_str;
    }
}
