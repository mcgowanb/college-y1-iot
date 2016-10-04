<?php

    $disabled = 'disabled=disabled';
    $url = "http://heatingcontroller.local/arduino/digital/8";
    $url = "http://www.example.com";

    function checkHeatingStatus()
    {
        global $disabled;
        global $url;

        $curl = curl_init($url);
        curl_setopt($curl,CURLOPT_RETURNTRANSFER,1);
        $result = curl_exec($curl);
        var_dump($result);
        curl_close($curl);

        $response = array(
            'msg' => 'Heating is currently Switched off',
            'onState' => $disabled,
            'offState' =>  ''
        );
        return $response;
    }

    function turnHeatingOn()
    {
        global $disabled;
        global $url;

        $url .= "/1";
        $curl = curl_init($url);
        curl_setopt($curl,CURLOPT_RETURNTRANSFER,1);
        curl_exec($curl);
        curl_close($curl);

        $response = array(
            'msg' => 'heating is currently switched on',
            'onState' => '',
            'offState' => $disabled
        );

        return $response;
    }

    function turnHeatingOff()
    {
        global $disabled;
        global $url;

        $url .= "/0";
        $curl = curl_init($url);
        curl_setopt($curl,CURLOPT_RETURNTRANSFER,1);
        curl_exec($curl);
        curl_close($curl);

        $response = array(
            'msg' => 'heating is currently switched off',
            'onState' => $disabled,
            'offState' => ''
        );
        return $response;
    }
