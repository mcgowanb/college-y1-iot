<?php
    require_once "methods.php";
    ?>
<html>
    <head>
        <title>Heating Control System</title>
        <meta charset="utf-8"/>

        <meta name="author" content="Brian McGowan">
        <link rel="stylesheet" type="text/css" href="css/style.css">
        <link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
    </head>
    <body>

        <?php
            $status = isset($_GET["on"]) ? (bool)($_GET["on"]) : false;

            if(empty($_GET)){
                //check status
                $state = checkHeatingStatus();
            }
            else if($status) {
                //turn heating on
                $state = turnHeatingOn();
            }
            else
            {
                //turn heating off
               $state = turnHeatingOff();
            }

            $offDisabled =  $state['onState'];
            $onDisabled = $state['offState'];
            $msg = $state['msg'];
        ?>
        <div class="main-body">
            <div class="row center-block">
                <div class="col-lg-12 title-text">
                    <h2>Heating Controller System</h2>
                    <hr>
                    <p><h4><?php echo $msg; ?></h4></p>
                </div>
                <div class="col-lg-12">
                    <form method="get">
                        <div class="button">
                            <button type="submit" name="on" value="1" class="btn btn-lg btn-success btn-block" <?php echo $onDisabled;?>>Turn On</button>
                        </div>
                    </form>

                </div>
                <div class="col-xs-12">
                    <form method="get">
                        <div class="button">
                            <button type="submit" name="on" value="0" class="btn btn-lg btn-danger btn-block" <?php echo $offDisabled;?>>Turn Off</button>
                        </div>
                    </form>

                </div>
            </div>
        </div>
    </body>
</html>