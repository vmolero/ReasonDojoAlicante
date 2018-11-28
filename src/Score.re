let component = ReasonReact.statelessComponent("Score");


let make = (~score, _children) => {
  ...component,
  render: _self =>
    <div className="score">
      {ReasonReact.string("Score: ")}{ReasonReact.string(string_of_int(score))}
    </div>
}