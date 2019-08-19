

/**
 * Copyright 2016 Evernote Corporation. All rights reserved.
 *
 * Toggle button to display a boolean choice. This is a pure component
 * that lets the parent own and pass the state of being checked.
 */
define(['require','react','classnames'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');

  var ToggleButtonComponent = React.createClass({
    displayName: 'ToggleButtonComponent',

    propTypes: {
      // Class name added to the button element
      btnClassName: React.PropTypes.string,

      // Class name to add only when isToggledOn is truthy
      btnClassNameOn: React.PropTypes.string,

      // use children to pass inside of button (text and/or img, etc)
      children: React.PropTypes.oneOfType([React.PropTypes.arrayOf(React.PropTypes.node), React.PropTypes.node]),

      // Pass true to add the btnClassNameOn css class to the element
      isToggledOn: React.PropTypes.bool,

      // Callback for toggling the button
      onToggle: React.PropTypes.func
    },

    render: function render() {
      var btnClassNames;
      btnClassNames = classnames(this.props.btnClassName, this.props.isToggledOn ? this.props.btnClassNameOn : false);

      return React.createElement(
        'span',
        {
          className: btnClassNames,
          onClick: this.props.onToggle
        },
        this.props.children
      );
    }
  });

  return ToggleButtonComponent;
});