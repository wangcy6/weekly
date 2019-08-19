

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react'],function (require) {
  

  var React = require('react');

  /**
   * An img element that can take additional `errorSrc` parameters, causing a fallback
   * image to be shown whenever the main `src` image cannot be loaded.
   */
  var FallbackImg = React.createClass({
    displayName: 'FallbackImg',

    propTypes: {
      alt: React.PropTypes.string,
      className: React.PropTypes.string,
      errorSrc: React.PropTypes.string.isRequired,
      errorSrc2x: React.PropTypes.string,
      src: React.PropTypes.string.isRequired,
      src2x: React.PropTypes.string
    },

    componentWillMount: function componentWillMount() {
      this.setState({
        src: this.props.src,
        src2x: this.props.src2x
      });
    },

    componentWillReceiveProps: function componentWillReceiveProps(nextProps) {
      if (this.props.src !== nextProps.src) {
        // If the src changed, then ensure that the fallback image is no longer shown.
        this.setState({
          src: nextProps.src,
          src2x: nextProps.src2x
        });
      }
    },

    onError: function onError() {
      this.setState({
        src: this.props.errorSrc,
        src2x: this.props.errorSrc2x
      });
    },

    render: function render() {
      return React.createElement('img', {
        className: this.props.className,
        onError: this.onError,
        src: this.state.src,
        srcSet: this.state.src2x && this.state.src2x + ' 2x',
        alt: this.props.alt
      });
    }
  });

  return FallbackImg;
});