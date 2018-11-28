let component = ReasonReact.statelessComponent("Button");

/* Button.re */
let make = (~text, ~onClick, _children) => {
  ...component,
  render: _self =>
    <button className="button" onClick>
      {ReasonReact.string(text)}
    </button>
}