<?php 
	include_once('data-user-profile.tpl.php'); 
?>

<div id="profile-wrapper">
	<!--Block met profiel informatie -->
	<div>
		<div class="container">
			<div class="float d170"><?PHP print $profile_picture; ?></div>
			<div class="float d430">
				<table>
					<tr>
						<td colspan="2"><h2><?PHP print $profile_naam; ?></h2></td>
					</tr>
					<tr>
						<td colspan="2">
							<table>
								<tr>
									<td><?PHP print $profile_functie; ?></td>
									<td>&nbsp;bij&nbsp;</td>
									<td><?PHP print $profile_organisatie; ?></td>
								</tr>
							</table>
					</tr>
					<tr>
						<td>verjaardag:</td>
						<td><?PHP print $profile_geboorte; ?></td>
					</tr>
					<tr>
						<td>Woonplaats:</td>
						<td><?PHP print $profile_woonplaats; ?></td>
					</tr>
					<tr>
						<td>Hobby's:</td>
						<td><?PHP print $profile_hobby; ?></td>
					</tr>					
				</table>
			
			
			
			
			</div>
			<div class="float d200">social media</div>
			<div class="clearfix"></div>
		</div>
	</div>

	<!--Block met menu werk informatie -->
	<div>
		<div class="container float d155">menu
		</div>
		<div class="container float d630">werksfeer
		</div>	
		<div class="clearfix"></div>
	</div>

	<!--Block met profiel omschrijving -->	
	<div>
		<div class="container d800"><?PHP print $profile_omschrijving; ?></div>
	</div>
	
	<!--Block met profiel voortgang -->	
	<div>
		<div class="container float d385">voortgang
		</div>
		<div class="container float d400">ranking
		</div>	
		<div class="clearfix"></div>
	</div>
	
	<!--Block met activiteiten en scores -->	
	<div>
		<div class="container d800"> 
			<table>
				<tr>
					<td><?PHP print $profile_eerste_grafiek; ?></td>
					<td><?PHP print $profile_tweede_grafiek; ?></td>
				</tr>
			</table>	
		</div>	
	</div>
	
	<!--Block met spel statistieken -->	
	<div>
		<div class="container d800">statistieken
		</div>
	</div>
</div>