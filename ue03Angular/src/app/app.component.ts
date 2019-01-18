import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  public title = 'ue03Angular';
  public clock = '??:??:??';
  public items = ['1', '2', '3'];

  constructor () {
    this.clock = new Date().toLocaleTimeString();
    setInterval (  () => this.handleTimer(), 1000);
  }

  private handleTimer() {
    this.clock = new Date().toLocaleTimeString();
    this.items.push('4');
  }

}
