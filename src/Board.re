let component = ReasonReact.statelessComponent("Board");



let make = (~activeMole, ~onHit, _children) => {
  ...component,
  render: _self =>
    <div className="board">
      {
        Belt.Array.range(0, 8)
        ->Belt.Array.map(num => 
            <div className="board-item">
              <div
                className={ activeMole === num ? "mole visible" : "mole" }
                onClick={_click => onHit()}
              ></div>
              <div className="ground"></div>
            </div>
        )
        ->ReasonReact.array
      }
    </div>
}