import {Component} from 'angular2/core';
import { RouteConfig, ROUTER_DIRECTIVES, ROUTER_PROVIDERS } from 'angular2/router';

import { CoinsComponent } from './coins.component';
import { CountriesComponent } from './countries.component';
import { AddCountryComponent } from './add-country.component';

@Component({
    selector: 'my-app',
    templateUrl: 'app/app.component.html',
    directives: [ROUTER_DIRECTIVES],
    providers: [
        ROUTER_PROVIDERS
  ]
})

@RouteConfig([
    {
        path: '/',
        name: 'Coins',
        component: CoinsComponent,
        useAsDefault: true
    },
    {
        path: '/countries',
        name: 'Countries',
        component: CountriesComponent
    },
    {
        path: '/addcountry',
        name: 'AddCountry',
        component: AddCountryComponent
    }
])
    
export class AppComponent { }
