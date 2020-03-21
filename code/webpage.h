R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  </head>
  <body>
    <div class="container-fluid">
      <div class="row" style="height: 33.33%; padding-top: 1em; padding-bottom:1em">
        <div class="col-xs-12" style="text-align: center; height: 100%">
          <button id="drive" type="button" class="btn btn-default" style="height: 100%; width: 100%" onmousedown='makeAjaxCall("door")' >DOOR</button>
        </div>
      </div>
      <div class="row" style="height: 33.33%; padding-bottom:1em">
        <div class="col-xs-12" style="height: 100%; text-align: center">
          <button id="left" type="button" class="btn btn-default" style="height: 100%; width: 100%" onmousedown='makeAjaxCall("lightOn")' >lightOn</button>
        </div>
      </div>
      <div class="row" style="height: 33.33%; padding-bottom:1em">
        <div class="col-xs-12" style="height: 100%; text-align: center">
          <button id="back" type="button" class="btn btn-default" style="height: 100%; width: 100%" onmousedown='makeAjaxCall("lightOff")' >lightOff</button>
        </div>
      </div>
    </div>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <script> function makeAjaxCall(url){$.ajax({"url": url})}</script>
  </body>
</html>
)"
