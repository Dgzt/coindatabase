package hu.dgzt.coindatabase.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * The route controller.
 * 
 * @author Dgzt
 */
@Controller
public class RouteController {

	/**
	 * Redirect to the index.html.
	 */
	@RequestMapping({
		"/countries",
		"/addcountry"
	})
	public String index() {
		return "forward:/index.html";
	}
}
