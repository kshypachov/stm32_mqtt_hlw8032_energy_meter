/*
 * web_pages.h
 *
 *  Created on: Jan 16, 2024
 *      Author: kirill
 */

#ifndef INC_WEB_PAGES_H_
#define INC_WEB_PAGES_H_

#define index_page			"<!DOCTYPE html>\r\n"\
							"<html lang=\"ua\">\r\n"\
							"<meta charset=\"windows-1251\">\r\n"\
							"<head>\r\n"\
							"	<style>\r\n"\
							"		h1 {text-align: center;}\r\n"\
							"		h2 {text-align: center;}\r\n"\
							"		h3 {text-align: center;}\r\n"\
							"		p {text-align: center;}\r\n"\
							"		div {text-align: center;}\r\n"\
							"		a {text-align: center;}\r\n"\
							"	</style>\r\n"\
							"</head>\r\n"\
							"<body>\r\n"\
							"	<h2>Головна сторінка</h2>\r\n"\
							"	<h3>Модуль SHY-DI3-DO3</h3>\r\n"\
							"	<!-- <div><a href=\"settings_network\">Налаштування мережі</a></div> -->\r\n"\
							"	<div><a href=\"mqtt.html\">Налаштування MQTT</a></div>\r\n"\
							"	<div><a href=\"settings_MODBUS_TCP.html\">Налаштування ModbusTCP</a></div>\r\n"\
							"	<div><a href=\"settings_MQTT\">Інформація про модуль</a></div>\r\n"\
							"	<div><a href=\"restart.cgi\" target=\"_blank\">Перезавантаження</a></div>\r\n"\
							"	</body>\r\n"\
							"</html>\r\n"

#define conf_page_mqtt		"<!DOCTYPE html>\r\n"\
							"<html lang=\"ua\">\r\n"\
							"<head>\r\n"\
							"<meta charset=\"utf-8\">\r\n"\
							"	<style>\r\n"\
							"		h2 {text-align: center;}\r\n"\
							"		form {text-align: center;}\r\n"\
							"	</style>\r\n"\
							"</head>\r\n"\
							"<body>\r\n"\
							"	<h2>MQTT Settings page</h2>\r\n"\
							"	<form action=\"settings_mqtt.cgi\" method=\"post\" target=\"_blank\">\r\n"\
							"	<fieldset>\r\n"\
							"		<legend>Settings:</legend>\r\n"\
							"			<div style=\"display:flex;flex-direction:row;justify-content:center\">\r\n"\
							"				<div style=\"display:flex;flex-direction:column;align-items:end;justify-content:space-between\">\r\n"\
							"					<label for=\"Enable\">Enable MQTT:</label>\r\n"\
							"					<br>\r\n"\
							"					<label for=\"login\">Login:</label>\r\n"\
							"					<label for=\"pass\">Password:</label>\r\n"\
							"					<label for=\"uri\">MQTT Server uri:</label>\r\n"\
							"					<label for=\"port\">MQTT Server port:</label>\r\n"\
							"				</div>\r\n"\
							"				<div style=\"display:flex;flex-direction:column;margin-left:20px;width:200px\">\r\n"\
							"					<div style=\"display:flex;flex-direction:row\">\r\n"\
							"						<input type=\"radio\" name=\"mqtt\" value=\"1\" checked> Так \r\n"\
							"						<input type=\"radio\" name=\"mqtt\" value=\"0\"> Ні \r\n"\
							"					</div>\r\n"\
							"					<br>\r\n"\
							"					<input type=\"text\" id=\"login\" name=\"login\" maxlength=\"30\">\r\n"\
							"					<input type=\"password\" id=\"password\" name=\"password\" maxlength=\"30\">\r\n"\
							"					<input type=\"text\" id=\"uri\" name=\"uri\" maxlength=\"30\" \">\r\n"\
							"					<input type=\"number\" id=\"port\" name=\"port\" min=\"1\" max=\"65535\" placeholder = \"by default 1883\" >\r\n"\
							"				</div>\r\n"\
							"			</div>\r\n"\
							"			<br>\r\n"\
							"			<input type=\"submit\" value=\"Submit\" >\r\n"\
							"	</fieldset>\r\n"\
							"	</form>\r\n"\
							"</body>\r\n"\
							"</html>\r\n"

#define setting_resistance_sens_page	"<!DOCTYPE html>\r\n"\
								"<html lang=\"ua\">\r\n"\
								"<head>\r\n"\
								"<meta charset=\"utf-8\">\r\n"\
								"	<style>\r\n"\
								"		h2 {text-align: center;}\r\n"\
								"		form {text-align: center;}\r\n"\
								"	</style>\r\n"\
								"</head>\r\n"\
								"<body>\r\n"\
								"	<h2>Power settings page</h2>\r\n"\
								"	<form action=\"settings_resistance.cgi\" method=\"post\" target=\"_blank\">\r\n"\
								"	<fieldset>\r\n"\
								"		<legend>Settings:</legend>\r\n"\
								"			<div style=\"display:flex;flex-direction:row;justify-content:center\">\r\n"\
								"				<div style=\"display:flex;flex-direction:column;align-items:end;justify-content:space-between\">\r\n"\
								"					<label for=\"shunt\">Value :</label>\r\n"\
								"				</div>\r\n"\
								"				<div style=\"display:flex;flex-direction:column;margin-left:20px;width:200px\">\r\n"\
								"					<br>\r\n"\
								"					<input type=\"number\" id=\"shunt\" name=\"shunt\" step=0.00000000001>\r\n"\
								"				</div>\r\n"\
								"			</div>\r\n"\
								"			<br>\r\n"\
								"			<input type=\"submit\" value=\"Submit\" >\r\n"\
								"	</fieldset>\r\n"\
								"	</form>\r\n"\
								"</body>\r\n"\
								"</html>\r\n"

#endif /* INC_WEB_PAGES_H_ */
