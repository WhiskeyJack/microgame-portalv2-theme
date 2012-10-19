<?php
#profile picture
$profile_picture =  render($user_profile['user_picture']); 

#profile table data:
$profile_naam = render($user_profile['field_volledige_naam']);
$profile_functie = render($user_profile['field_functie']);
$profile_organisatie = render($user_profile['field_organisatie']);
$profile_geboorte = render($user_profile['field_geboorte_datum']);
$profile_woonplaats = render($user_profile['field_woonplaats']);
$profile_hobby = render($user_profile['field_activiteiten']);

	#profile table output:
	if (!$profile_functie) {
		$profile_functie = "Werkzaam";
		}
		
#social media icons

#profile table data:
$profile_omschrijving = render ($user_profile['field_omschrijving']); 

#score grafiek 1:

$profile_eerste_grafiek = "
		<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>   
			<script type=\"text/javascript\">
      google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});
      google.setOnLoadCallback(drawChart);
      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['MicroGame', 'Aantal keer gespeeld'],
          ['Service with a smile',     11],
          ['circle lines',      2],
          ['time nanny',  2],
          ['dare 2 care', 2],
          ['IDMK',    7]
        ]);

        var options = {
          title: 'My Daily Activities'		  
        };

        var chart = new google.visualization.PieChart(document.getElementById('chart_div'));
        chart.draw(data, options);
		
		chart.draw(data, {
			title: 'Meest gespeelde games',
			backgroundColor: '#ddd',
			is3D: true
			});
		
      }
    </script>

    <div id=\"chart_div\" style=\"width: 350px; height: 200px;\"></div>";

$profile_tweede_grafiek = "
		<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>   
			<script type=\"text/javascript\">
      google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});
      google.setOnLoadCallback(drawChart);
      function drawChart() {
        var data = google.visualization.arrayToDataTable([
          ['MicroGame', 'minuten'],
          ['Service with a smile',     80],
          ['circle lines',     35],
          ['time nanny',  15],
          ['dare 2 care', 15],
          ['IDMK',    5]
        ]);

        var options = {
          title: 'My Daily Activities'		  
        };

        var chart = new google.visualization.PieChart(document.getElementById('chart_div2'));
        chart.draw(data, options);
		
		chart.draw(data, {
			title: 'Tijd per game gespeeld',
			backgroundColor: '#ddd',
			is3D: true
			});
		
      }
    </script>

    <div id=\"chart_div2\" style=\"width: 350px; height: 200px;\"></div>";







?>