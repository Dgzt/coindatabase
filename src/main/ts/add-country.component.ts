import { Component }    from 'angular2/core';
import { NgForm }       from 'angular2/common';

import { Country }      from './country';

@Component({
    selector: 'my-add-country',
    templateUrl: 'app/add-country.component.html'
})

export class AddCountryComponent {
    
    model : Country = {name: ''};
    
    onSubmit() {
        // TODO - Send the model to the server
        console.log(this.model);
    }
}
